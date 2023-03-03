#ifndef irc_HPP
# define irc_HPP

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
# include "User.hpp"
# include "Channel.hpp"
# include "Server.hpp"
# include "commands.hpp"
# include "utils.hpp"

#define VECTOR std::vector<User>
#define ITERATOR std::vector<User>::iterator

void    start_irc (int port, std::string password);
int     getInfoUser(User* new_Usert, char *buffer, std::string password);
void    checkPassword (User* new_user, char* buffer, std::string password);
void    setUsername (User* new_user, char* buffer);
void    setNickname (User* new_user, char* buffer);
int     getInfoUser (User* new_user, char* buffer, std::string password, std::vector<User> users);
void    createUser (int new_socket, VECTOR* users, int* max_sd, int* number_of_users);
int     checkDuplicateNick(std::string to_check, std::vector<User> users, int sd);
int     checkdoublonuser(char *tocheck, std::vector<User> users, int sd);

template <class T>
void    printVector (std::vector<T>& myVector) {
    std::cout << "Taille du vecteur : " << myVector.size() << "\n";
    for (long unsigned int i = 0; i < myVector.size(); i++)
        std::cout << "   value "  << i << " == " <<  myVector[i] << std::endl;
}

#endif
