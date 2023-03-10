#pragma once

# define USER_VECTOR std::vector<User>
# define USER_ITERATOR std::vector<User>::iterator
# define STRING_VECTOR std::vector<std::string>
# define STRING_ITERATOR std::vector<std::string>::iterator
# define CHANNEL_VECTOR std::vector<Channel>
# define CHANNEL_ITERATOR std::vector<Channel>::iterator

class User;
class Channel;
class Server;

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
const int MAX_USERS = 10;
const int BUFFER_SIZE = 1024;

enum    e_info_status {
    NEW_CONNEXION,
    ENTER_SERVPWD,
    SERVPWD_OK,
    WRONG_SERVPWD,
    NEW_USER,
    WELCOME,
    NICK_TAKEN,
    INVALID_NICK,
    KNOWN_USER,
    USERPWD_OK,
    WRONG_USERPWD,
    INFO_OVER,
    WAIT_COMMAND
};

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
void    startIrc (const int port, const std::string password);
void    createUser (int new_socket, USER_VECTOR& users, int& max_sd, int& number_of_users);
int     checkDuplicateNick (std::string to_check, USER_VECTOR users);
int     checkDuplicateUser (std::string to_check, USER_VECTOR users);
int     checkCommand (int sd, std::string to_check, Server& irc_server);
void    createChannel (User executer, std::string channel_name, Server& irc_server);
CHANNEL_ITERATOR     findChannel (std::string channel_name, Server& irc_server);
