#include "../includes/irc.hpp"

//  ---------------------------------    Redir function  --------------------------------------

void redirectFonction(User executer, char *buffer, std::vector<User>* users_tab, Server& irc_server, std::string password)
{
    (void)password;
    std::string string_buffer (buffer);
    if (string_buffer.empty ())
        return ;
    std::vector<std::string> bufferSplit = splitString (string_buffer);
    if (bufferSplit[0] == "/PVTMSG" or bufferSplit[0] == "/w")
        msg(executer, bufferSplit, *users_tab);
    else if (bufferSplit[0] == "/NICK")
        nick(executer, bufferSplit, *users_tab);
    else if (bufferSplit[0] == "/QUIT")
        quit(executer);
    else if (bufferSplit[0] == "/PING")
        ping(executer, bufferSplit);
    else if (bufferSplit[0] == "/MOTD")
        motd(executer);
    else if (bufferSplit[0] == "/AWAY")
        away(executer, bufferSplit);
    else if (bufferSplit[0] == "/join")
        join(executer, bufferSplit, irc_server);
    
        // else if (strcmp(buffer_spli, "/part") == 0)
        //     part(users_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/users") == 0)
        //     users(users_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/names") == 0)
        //     names(users_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/list") == 0)
        //     list(users_tab[newsocket], buffer);
    else
        print_message (executer.sd, "Unknown command.\n");
}

void start_irc(int port, std::string password)
{
    Server    irc_server (port, password); 
    int       server_fd = irc_server.getFd ();
    int       address_length = irc_server.getAddressLength ();
    int       new_socket, activity, valread, sup = -1;
    int       max_sd = server_fd;
    int       number_of_users = 0;
    ITERATOR  supp;
    fd_set    read_fds;
    char      buffer[BUFFER_SIZE];
    SOCKADDR_IN   server_address = irc_server.getAddress ();

    while (true) {
        FD_ZERO(&read_fds);
        FD_SET(server_fd, &read_fds);
        for (ITERATOR it = irc_server.users.begin(); it != irc_server.users.end(); ++it)
            FD_SET((*it).sd, &read_fds);
        activity = select(max_sd + 1, &read_fds, NULL, NULL, NULL);
        if ((activity < 0) && (errno!=EINTR))
            print_error ("Select error");
        if (FD_ISSET(server_fd, &read_fds)) {
            if ((new_socket = accept(server_fd, (SOCKADDR*)&server_address, (socklen_t*)&address_length))<0)
                print_error ("Socket creation error");
			createUser (new_socket, &irc_server.users, &max_sd, &number_of_users);
        }
        for (ITERATOR it = irc_server.users.begin(); it != irc_server.users.end(); it++) {
            memset(buffer, 0, BUFFER_SIZE);
            if (FD_ISSET((*it).sd, &read_fds)) {
                valread = read((*it).sd, buffer, BUFFER_SIZE);
                if (valread == 0) {
                    getpeername((*it).sd, (SOCKADDR*)&server_address, (socklen_t*)&address_length);
                    std::cout << "User disconnected: " << inet_ntoa(server_address.sin_addr) << ":" \
                        << ntohs(server_address.sin_port) << std::endl; // clear user non necessaire ?
                    number_of_users--;
                    sup = (*it).sd;
                    supp = it;
                }
                else if (valread == -1 && errno == EAGAIN)
                    print_error ("Reading failure");
                else {
                    if (getInfoUser(it.base(), buffer, password, irc_server.users) == 0)
                        redirectFonction(*it, buffer, &irc_server.users, irc_server, password);
                    buffer[valread] = '\0';
                    getpeername((*it).sd, (SOCKADDR*)&server_address, (socklen_t*)&address_length);
                }
            }
        }
        if (sup > 0){
            close(sup);
            irc_server.users.erase(supp);
            sup = -1;
        }
    }
}
