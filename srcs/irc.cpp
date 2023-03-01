#include "../includes/irc.hpp"

#define VECTOR std::vector<clien>
#define ITERATOR std::vector<clien>::iterator

void    getInfoClient (clien* new_client, char* buffer, std::string password) {
    removeInvisibleChars(buffer);
    std::string message;
    std::string commande;

    if (new_client->password == "")
    {
        if (password.compare(buffer) == 0)
        {
            new_client->password = buffer;
            write(new_client->sd, "Enter your username: ", 21);
            return ;
        }
        else
        {
            write(new_client->sd, "Wrong password, try again: ", 27);
            return ;
        }
    }
    else if (new_client->username == "")
    {
        new_client->username = buffer;
        write(new_client->sd, "Enter your nickname: ", 21);
        return;
    }
    else if (new_client->nickname == "")
    {
        // Remove any newline or carriage return characters from the end of the buffer
        int len = strlen(buffer);
        while (len > 0 && (buffer[len-1] == '\n' || buffer[len-1] == '\r')) {
            buffer[--len] = '\0';
        }

        new_client->nickname = buffer;
        message = "Welcome " + new_client->username + " " + new_client->nickname + " !\n";
        write(new_client->sd, message.c_str(), message.length());
        commande = "Enter a command: \n" ;
        write(new_client->sd, commande.c_str(), commande.length());

        return;
    }
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
    VECTOR    clients;
    SOCKADDR_IN   server_address = irc_server.getAddress ();

    while (true) {
        FD_ZERO(&read_fds);
        FD_SET(server_fd, &read_fds);

        if (clients.empty () == 0) {
            for (std::vector<clien>::iterator it = clients.begin(); it != clients.end(); ++it)
                FD_SET((*it).sd, &read_fds);
        }
        activity = select(max_sd + 1, &read_fds, NULL, NULL, NULL);
        if ((activity < 0) && (errno!=EINTR))
            print_error ("Select error");
        if (FD_ISSET(server_fd, &read_fds)) {
            if ((new_socket = accept(server_fd, (SOCKADDR*)&server_address, (socklen_t*)&address_length))<0)
                print_error ("Socket creation error");
            fcntl(new_socket, F_SETFL, O_NONBLOCK);
            max_sd = std::max (max_sd, new_socket);
            if (CheckClientExists(clients, new_socket) == 0)
            {
                if (number_of_clients >= MAX_CLIENTS)
                    exit(0); // a changer en fonction qui close toute les socket
                printf("New client connected\n");
                clien new_client (new_socket);
                clients.push_back(new_client);
                write(new_socket, "Welcome to the server\n", 22);
                write(new_socket, "Enter the password\n", 19);
                number_of_clients++;
            }
        }
        for (ITERATOR it = clients.begin(); it != clients.end(); it++) {
            memset(buffer, 0, BUFFER_SIZE);
            if (FD_ISSET((*it).sd, &read_fds)) {
                valread = read((*it).sd, buffer, BUFFER_SIZE);
                if (valread == 0) {
                    getpeername((*it).sd, (SOCKADDR*)&server_address, (socklen_t*)&address_length);
                    printf("Client disconnected: %s:%d\n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));
                    number_of_clients--;
                    sup = (*it).sd;
                    supp = it;
                }
                else if (valread == -1 && errno == EAGAIN)
                    print_error ("Reading failure");
                else {
                    for (ITERATOR it = clients.begin (); it != clients.end (); it++)
                        if ((*it).sd == new_socket) {
                            getInfoClient(it.base (), buffer, password);
                            //redirectFonction((*it).sd, buffer, clients, password);    
                        }
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
