#include "../includes/irc.hpp"

#define VECTOR std::vector<clien>
#define ITERATOR std::vector<clien>::iterator

void    checkPassword (clien* new_client, char* buffer, std::string password) {
        if (password.compare(buffer) == 0) {
            new_client->password = buffer;
            write(new_client->sd, "Enter your username: ", 21);
        }
        else
            write(new_client->sd, "Wrong password, try again: ", 27);
}

void    setUsername (clien* new_client, char* buffer) {
        new_client->username = buffer;
        write(new_client->sd, "Enter your nickname: ", 21);
}

void    setNickname (clien* new_client, char* buffer) {
        new_client->nickname = buffer;
}

void    writeWelcomeMessage (clien* new_client) {
    std::string message;

    message = "Welcome " + new_client->username + " " + new_client->nickname + " !\n";
    write(new_client->sd, message.c_str(), message.length());
    write(new_client->sd, "Enter a command: \n", 19);
}

void    getInfoClient (clien* new_client, char* buffer, std::string password) {
    removeInvisibleChars(buffer);

    if (new_client->password == "") {
        checkPassword (new_client, buffer, password);
        return;
    }
    else if (new_client->username == "") {
        setUsername (new_client, buffer);
        return;
    }
    else if (new_client->nickname == "") {
        setNickname (new_client, buffer);
        writeWelcomeMessage (new_client);
        return;
    }
}

void    createClient (int new_socket, VECTOR* clients, int* max_sd, int* number_of_clients) {
    clien new_client (new_socket);

    if (CheckClientExists(*clients, new_socket) == 0)
    {
        if (*number_of_clients >= MAX_CLIENTS)
            exit(0); // a changer en fonction qui close toute les socket
        std::cout << "New client connected" << std::endl;
        fcntl(new_socket, F_SETFL, O_NONBLOCK);
        clients->push_back (new_client);
        *max_sd = std::max (*max_sd, new_socket);
        (*number_of_clients)++;
        write (new_socket, "Welcome to the server\n", 22);
        write (new_socket, "Enter the password\n", 19);
    }
    else
        //close new_socket?
        ;
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
