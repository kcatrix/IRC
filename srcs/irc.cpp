#include "../includes/irc.hpp"

extern int errno;

User    getUser (USER_VECTOR users, std::string nickname) {
    for (USER_ITERATOR it = users.begin (); it != users.end (); it++) {
        if (it->nickname == nickname)
            return *it;
    }
    return User ();
}

void    createChannel (User executer, std::string channel_name, Server& irc_server) {
        channel_name = "#" + channel_name;
        Channel     new_channel (channel_name);

        new_channel.ope.push_back (executer.nickname);
        new_channel.chan_users.push_back (executer);
        irc_server.channels.push_back (new_channel);
        print_message (executer.sd, "You created the channel " + irc_server.channels.back ().channel_name + "\n");
}

CHANNEL_ITERATOR     findChannel (std::string channel_name, Server& irc_server) {
    CHANNEL_ITERATOR    current_channel = irc_server.channels.begin ();
    while (current_channel != irc_server.channels.end ()) {
        if (current_channel->channel_name == channel_name)
            return current_channel;
        current_channel++;
    }
    return current_channel;
}

int     checkCommand (int sd, std::string to_check, Server& irc_server) {
    for (STRING_ITERATOR it = irc_server.commands_list.begin (); it != irc_server.commands_list.end (); it++)
        if (to_check == *it)
            return 1;
    if (to_check.empty () == 0)
        print_message (sd, "Unknown command.\n");
    return 0;
}

void    redirectFonction (User &executer, STRING_VECTOR bufferSplit, Server& irc_server) {
    if (checkCommand (executer.sd, bufferSplit[0], irc_server) == 1) {
        if (bufferSplit[0] == "/pvtmsg" or bufferSplit[0] == "/w")
            msg(executer, bufferSplit, irc_server.users, irc_server);
        else if (bufferSplit[0] == "/nick")
            nick(executer, bufferSplit, irc_server.users);
        else if (bufferSplit[0] == "/quit")
            quit(executer);
        else if (bufferSplit[0] == "/motd")
            motd(executer);
        else if (bufferSplit[0] == "/away")
            away(executer, bufferSplit);
		else if (bufferSplit[0] == "/op")
			op (executer, bufferSplit, irc_server);
		else if (bufferSplit[0] == "/deop")
			deop (executer, bufferSplit, irc_server);
        else if (bufferSplit[0] == "/join")
            join (executer, bufferSplit, irc_server);
        else if (bufferSplit[0] == "/kick")
            kick (executer, bufferSplit, irc_server);
        else if (bufferSplit[0] == "/invite")
            invite (executer, bufferSplit, irc_server);
        else if (bufferSplit[0] == "/ignore")
            ignore (executer, bufferSplit[1], irc_server);
        else if (bufferSplit[0] == "/accept")
            accept (executer, bufferSplit[1], irc_server);
        else if (bufferSplit[0] == "/ban")
            ban (executer, bufferSplit, irc_server);
        else if (bufferSplit[0] == "/unban")
            unban (executer, bufferSplit, irc_server);
        else if (bufferSplit[0] == "/userhost")
            userhost (executer, bufferSplit, irc_server);
        else if (bufferSplit[0] == "/part")
            part (executer, bufferSplit, irc_server);
        else if (bufferSplit[0] == "/names")
            names (executer, bufferSplit, irc_server);
        else if (bufferSplit[0] == "/list")
            list (executer, irc_server.channels);
        else if (bufferSplit[0] == "/help")
            help (executer, bufferSplit, irc_server.commands_list);
        else if (bufferSplit[0] == "/identify")
            identify (executer, bufferSplit[1]);
    }
}

void    askInput (const int sd, int& info_status) {
    if (info_status == NEW_CONNEXION) {
        print_message (sd, "Enter the password to access this server: ");
        info_status = ENTER_SERVPWD;
    }
    else if (info_status == SERVPWD_OK)
        print_message (sd, "Enter your nickname: ");
    else if (info_status == WRONG_SERVPWD) {
        print_message (sd, "Wrong password. Try again: ");
        info_status = ENTER_SERVPWD;
    }
    else if (info_status == NEW_USER)
        print_message (sd, "Enter your username: ");
    else if (info_status == NICK_TAKEN) {
        print_message (sd, "Nickname already in use, please try another one: ");
        info_status = SERVPWD_OK;
    }
    else if (info_status == KNOWN_USER) // && log_PWD_exist ?
        print_message (sd, "Enter your password to log in:(Enter if no pwd)");
    else if (info_status == INVALID_NICK) {
        print_message (sd, "Your nickname must start with a letter. Pick another one: ");
        info_status = SERVPWD_OK;
    }
    else if (info_status == USERPWD_OK) {
        print_message (sd, "Welcome back!\n");
        info_status = INFO_OVER;
    }
    else if (info_status == WRONG_USERPWD) {
        print_message (sd, "Wrong password. Try again: ");
        info_status = KNOWN_USER;
    }
    else if (info_status == WELCOME) {
        print_message (sd, "Welcome to our server! Type /help to see a list of the available commands.\n");
        info_status = INFO_OVER;
    }
    else
        info_status = WAIT_COMMAND;
}



void    readInfo (User& user, STRING_VECTOR bufferSplit, Server& irc_server);

void startIrc (const int port, const std::string password) {
    Server    irc_server (port, password); 
    int       server_fd = irc_server.getFd ();
    int       address_length = irc_server.getAddressLength ();
    int       new_socket, activity, valread;
    int       max_sd = server_fd;
    int       number_of_users = 0;
    fd_set    read_fds;
    char      buffer[BUFFER_SIZE];
    SOCKADDR_IN   server_address = irc_server.getAddress ();

    while (true) {
        FD_ZERO (&read_fds);
        FD_SET (server_fd, &read_fds);
        for (USER_ITERATOR it = irc_server.users.begin (); it != irc_server.users.end (); ++it) {
            if (it->sd != 0)
                FD_SET (it->sd, &read_fds);
        }
        if ((activity = select (max_sd + 1, &read_fds, NULL, NULL, NULL)) < 0)
            print_error ("Select error");
        if (FD_ISSET (server_fd, &read_fds)) {
            if ((new_socket = accept (server_fd, (SOCKADDR*)&server_address, (socklen_t*)&address_length))<0)
                print_error ("Socket creation error");
			createUser (new_socket, irc_server.users, max_sd, number_of_users);
        }
        for (USER_ITERATOR it = irc_server.users.begin (); it != irc_server.users.end (); it++) {
            memset (buffer, 0, BUFFER_SIZE);
            if (FD_ISSET (it->sd, &read_fds)) {
                valread = read (it->sd, buffer, BUFFER_SIZE);
                if (valread == 0) {
                    it->online = false;
                    std::cout << "User " << it->nickname << " went offline" << std::endl;
                    number_of_users--;
                    FD_CLR (it->sd, &read_fds);
                    close (it->sd);
                    it->sd = 0;
                }
                else if (valread == -1)
                    print_error ("Reading failure");
                else {
                    std::string string_buffer (buffer);
                    STRING_VECTOR bufferSplit = splitString (string_buffer);
                    readInfo (*it, bufferSplit, irc_server);
                    if (it->info == KNOWN_USER)
                        it->online = true;
                    askInput (it->sd, it->info);
                    if (it->info == WAIT_COMMAND)
                        redirectFonction (*it, bufferSplit, irc_server);
                }
            }
        }
    }
}
