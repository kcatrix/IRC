#include "../includes/irc.hpp"

extern int errno;

User    getUser (USER_VECTOR users, std::string nickname) {
    for (USER_ITERATOR it = users.begin (); it != users.end (); it++) {
        if(it->nickname == nickname)
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

void    redirectFonction (User &executer, STRING_VECTOR bufferSplit, std::vector<User>* users_tab, Server& irc_server)
{
    if (checkCommand (executer.sd, bufferSplit[0], irc_server) == 1) {
        if (bufferSplit[0] == "/pvtmsg" or bufferSplit[0] == "/w")
            msg(executer, bufferSplit, *users_tab, irc_server);
        else if (bufferSplit[0] == "/nick")
            nick(executer, bufferSplit, *users_tab);
        else if (bufferSplit[0] == "/quit")
            quit(executer);
        else if (bufferSplit[0] == "/ping")
            ping(executer, bufferSplit);
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

void start_irc (const int port, const std::string password) {
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
                std::string string_buffer (buffer);
                if (valread == 0) {
                    it->online = false;
                    std::cout << "User " << it->nickname << " went offline. (" << inet_ntoa (server_address.sin_addr) << ":" \
                        << ntohs (server_address.sin_port) << ")" << std::endl;
                    number_of_users--;
                    FD_CLR (it->sd, &read_fds);
                    close (it->sd);
                    it->sd = 0;
                }
                else if (valread == -1 && errno == EAGAIN)
                    print_error ("Reading failure");
                else {
                    STRING_VECTOR bufferSplit = splitString (string_buffer);
                    if (getInfoUser (it.base (), bufferSplit, password, irc_server.users) == 0){ 
                        redirectFonction (*it, bufferSplit, &irc_server.users, irc_server);
                    }
                }
            }
        }
    }
}
