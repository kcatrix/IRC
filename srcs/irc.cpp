#include "../includes/irc.hpp"

//  ---------------------------------    Redir function  --------------------------------------

void redirectFonction(User executer, char *buffer, std::vector<User>* users_tab, Server& irc_server, std::string password)
{
    (void)password;
    if (strlen(buffer) <= 0)
        return ;
    std::string string_buffer (buffer);
    char **bufferspli = ft_split(buffer, ' ');
    std::vector<std::string> bufferSplit = splitString (string_buffer);
    if (bufferSplit[0] == "/PVTMSG" or bufferSplit[0] == "/w")
        msg(executer, bufferSplit, *users_tab);
    else if (strcmp(bufferspli[0], "/NICK") == 0)
        nick(executer, buffer, users_tab);
    else if (strcmp(buffer, "/QUIT") == 0)
        quit(executer);
    else if (strcmp(bufferspli[0], "/PING") == 0)
        ping(executer, buffer);
    else if (strcmp(bufferspli[0], "/MODT") == 0)
        modt(executer);
    else if (strcmp(bufferspli[0], "/AWAY") == 0)
        away(executer, buffer);
    else if (bufferSplit[0] == "/join")
        join(executer, bufferSplit, irc_server);
    // il faut d'abbord split le buffer sur l'espace pour avoir argv[0]
    
        // if (strcmp(buffer_spli, "/nick") == 0)
        //     nick(users_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/part") == 0)
        //     part(users_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/users") == 0)
        //     users(users_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/msg") == 0)
        //     msg(users_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/names") == 0)
        //     names(users_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/list") == 0)
        //     list(users_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/quit") == 0)
        //     quit(users_tab[newsocket], buffer);
    else
        print_message (executer.sd, "Unknown command.\n");

    free_tab(bufferspli);
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
                    if (getInfoUser(it.base(), buffer, password, irc_server.users) == 0) // .base() pas risque ?
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
