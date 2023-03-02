#include "../includes/irc.hpp"

//  ---------------------------------    Redir function  --------------------------------------

void redirectFonction(clien executer, char *buffer, std::vector<clien>* client_tab, std::string password)
{
    (void)password;
    if (strlen(buffer) <= 0)
        return ;
    char **bufferspli = ft_split(buffer, ' ');
    if (strcmp(bufferspli[0], "/PVTSMG") == 0)
        msg(executer, buffer, *client_tab);
    else if (strcmp(bufferspli[0], "/NICK") == 0)
        nick(executer, buffer, client_tab);
    else if (strcmp(buffer, "/QUIT") == 0)
        quit(executer);
    else if (strcmp(bufferspli[0], "/PING") == 0)
        ping(executer, buffer);
    // il faut d'abbord split le buffer sur l'espace pour avoir argv[0]
    
        // if (strcmp(buffer_spli, "/nick") == 0)
        //     nick(client_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/join") == 0)
        //     join(client_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/part") == 0)
        //     part(client_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/users") == 0)
        //     users(client_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/msg") == 0)
        //     msg(client_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/names") == 0)
        //     names(client_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/list") == 0)
        //     list(client_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/quit") == 0)
        //     quit(client_tab[newsocket], buffer);
    else
        write(executer.sd, "Command not found\n", 18);

    free_tab(bufferspli);
}

void start_irc(int port, std::string password)
{
    Server    irc_server (port, password); 
    int       server_fd = irc_server.getFd ();
    int       address_length = irc_server.getAddressLength ();
    int       new_socket, activity, valread, sup = -1;
    int       max_sd = server_fd;
    int       number_of_clients = 0;
    ITERATOR  supp;
    fd_set    read_fds;
    char      buffer[BUFFER_SIZE];
    VECTOR    clients(0);
    SOCKADDR_IN   server_address = irc_server.getAddress ();

    while (true) {
        FD_ZERO(&read_fds);
        FD_SET(server_fd, &read_fds);
        for (ITERATOR it = clients.begin(); it != clients.end(); ++it)
            FD_SET((*it).sd, &read_fds);
        activity = select(max_sd + 1, &read_fds, NULL, NULL, NULL);
        if ((activity < 0) && (errno!=EINTR))
            print_error ("Select error");
        if (FD_ISSET(server_fd, &read_fds)) {
            if ((new_socket = accept(server_fd, (SOCKADDR*)&server_address, (socklen_t*)&address_length))<0)
                print_error ("Socket creation error");
			createClient (new_socket, &clients, &max_sd, &number_of_clients);
        }
        for (ITERATOR it = clients.begin(); it != clients.end(); it++) {
            memset(buffer, 0, BUFFER_SIZE);
            if (FD_ISSET((*it).sd, &read_fds)) {
                valread = read((*it).sd, buffer, BUFFER_SIZE);
                if (valread == 0) {
                    getpeername((*it).sd, (SOCKADDR*)&server_address, (socklen_t*)&address_length);
                    std::cout << "Client disconnected: " << inet_ntoa(server_address.sin_addr) << ":" \
                        << ntohs(server_address.sin_port) << std::endl; // clear clien non necessaire ?
                    number_of_clients--;
                    sup = (*it).sd;
                    supp = it;
                }
                else if (valread == -1 && errno == EAGAIN)
                    print_error ("Reading failure");
                else {
                    if (getInfoClient(it.base(), buffer, password, clients) == 0) // .base() pas risque ?
                        redirectFonction(*it, buffer, &clients, password);
                    buffer[valread] = '\0';
                    getpeername((*it).sd, (SOCKADDR*)&server_address, (socklen_t*)&address_length);
                    std::cout << buffer << std::endl;
                }
            }
        }
        if (sup > 0){
            close(sup);
            clients.erase(supp);
            sup = -1;
        }
    }
}
