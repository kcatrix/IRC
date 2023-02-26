#include "../includes/serv.hpp"
#include "../includes/clien.hpp"
#include "../includes/utils.hpp"
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <cstdio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>
const int MAX_CLIENTS = 10;
const int BUFFER_SIZE = 1024;

//conseil jé utiliser select

Server::Server (int port) {
    _port = port;
    init_address ();
    create_socket ();
    loop ();
}

void    Server::init_address (void) {
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = htonl (INADDR_ANY);
    _address.sin_port = htons (_port);
    bzero (_address.sin_zero, sizeof(_address.sin_zero));
    _addrlen = sizeof (_address);
}

void    Server::create_socket (void) {
    _server_fd = socket (AF_INET, SOCK_STREAM, 0);
    if (_server_fd < 0)
        print_error ("Server socket creation error\n");
    fcntl(_server_fd, F_SETFL, O_NONBLOCK);
    if (bind (_server_fd, (SOCKADDR*) &_address, sizeof(_address)) < 0)
        print_error ("Server socket binding error\n");
    std::cout << "Listening on port " << _port << std::endl;
    if (listen (_server_fd, MAX_CLIENTS) < 0)
        print_error ("Server socket listening error\n");
}

void    Server::loop (void) {
    int new_socket, activity, valread, sd, sup = -1;
    int max_sd;
    std::vector<int>::iterator supp;
    fd_set read_fds;
    char buffer[BUFFER_SIZE] = {0};
    std::string message = "Please enter your username\n";
    std::vector<int> clients;

    while (true) {
        FD_ZERO(&read_fds);
        FD_SET(_server_fd, &read_fds);
        max_sd = _server_fd;

        for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
            sd = *it;
            FD_SET(sd, &read_fds);
            if (sd > max_sd) max_sd = sd;
        }
        activity = select(max_sd + 1, &read_fds, NULL, NULL, NULL);

        if ((activity < 0) && (errno!=EINTR)) {
            printf("select error");
        }

        if (FD_ISSET(_server_fd, &read_fds)) {
            if ((new_socket = accept(_server_fd, (SOCKADDR*)&_address, (socklen_t*)&_addrlen))<0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            // Set the new client socket to non-blocking mode
            fcntl(new_socket, F_SETFL, O_NONBLOCK);
            clients.push_back(new_socket);
            printf("New client connected\n");
            //clien *client_tab = new clien("john", "doe"); 


        }

        for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); it++) {
            sd = *it;

            if (FD_ISSET(*it, &read_fds)) {
                // Receive data from the client
                valread = read(*it, buffer, BUFFER_SIZE);
                if (valread == 0) {
                    // Client disconnected
                    getpeername(sd, (struct sockaddr*)&_address, (socklen_t*)&_addrlen);
                    printf("Client disconnected: %s:%d\n", inet_ntoa(_address.sin_addr), ntohs(_address.sin_port));
                    sup = *it;
                    supp = it;
                }
                else if (valread == -1 && errno == EAGAIN) {
                    std::cout << "passe\n";
                    // No data available yet
                    continue;
                }
                else {

                    // send(it, "", strlen(buffer), 0);
                    buffer[valread] = '\0';
                    getpeername(sd, (struct sockaddr*)&_address, (socklen_t*)&_addrlen);
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

Server::~Server (void) { close (_server_fd); }

