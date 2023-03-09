#ifndef irc_HPP
# define irc_HPP

# define USER_VECTOR std::vector<User>
# define USER_ITERATOR std::vector<User>::iterator
# define STRING_VECTOR std::vector<std::string>
# define STRING_ITERATOR std::vector<std::string>::iterator
# define CHANNEL_VECTOR std::vector<Channel>
# define CHANNEL_ITERATOR std::vector<Channel>::iterator

class User;
class Channel;
class Server;

# include <signal.h>
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

User    getUser (USER_VECTOR users, std::string nickname);
void    start_irc (int port, std::string password);
int     getInfoUser(User* new_User, STRING_VECTOR bufferSplit, std::string password, USER_VECTOR users);
void    checkPassword (User* new_user, char* buffer, std::string password);
void    setUsername (User* new_user, char* buffer);
void    setNickname (User* new_user, char* buffer);
void    createUser (int new_socket, USER_VECTOR* users, int* max_sd, int* number_of_users);
int     checkDuplicateNick(std::string to_check, std::vector<User> users);
int     checkdoublonuser(char *tocheck, std::vector<User> users, int sd);
int     checkCommand(int sd, std::string to_check, Server& irc_server);
void    createChannel (User executer, std::string channel_name, Server& irc_server);
CHANNEL_ITERATOR     findChannel (std::string channel_name, Server& irc_server);

template <class T>
void    printVector (std::vector<T>& myVector) {
    std::cout << "Taille du vecteur : " << myVector.size() << "\n";
    for (long unsigned int i = 0; i < myVector.size(); i++)
        std::cout << "   value "  << i << " == " <<  myVector[i] << std::endl;
}


#endif
