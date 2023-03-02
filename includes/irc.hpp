#ifndef irc_HPP
# define irc_HPP

# include "clien.hpp"
# include "commands.hpp"
# include "utils.hpp"
# include "Server.hpp"
#include <signal.h>
# include <iostream>
# include <cerrno>
# include <cstring>
# include <stdlib.h>
# include <vector>
# include <string>
# include <netdb.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <arpa/inet.h>

#define VECTOR std::vector<clien>
#define ITERATOR std::vector<clien>::iterator

void    start_irc (int port, std::string password);
int     getInfoClient(clien* new_client, char *buffer, std::string password);
void    checkPassword (clien* new_client, char* buffer, std::string password);
void    setUsername (clien* new_client, char* buffer);
void    setNickname (clien* new_client, char* buffer);
int     getInfoClient (clien* new_client, char* buffer, std::string password, std::vector<clien> clients);
void    createClient (int new_socket, VECTOR* clients, int* max_sd, int* number_of_clients);
int     checkdoublonnick(char *tocheck, std::vector<clien> clients, int sd);
int     checkdoublonuser(char *tocheck, std::vector<clien> clients, int sd);

template <class T>
void    printVector (std::vector<T>& myVector) {
    std::cout << "Taille du vecteur : " << myVector.size() << "\n";
    for (long unsigned int i = 0; i < myVector.size(); i++)
        std::cout << "   value "  << i << " == " <<  myVector[i] << std::endl;
}

#endif
