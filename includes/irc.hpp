#pragma once

# include <iostream>
# include <cstring>
# include <vector>
# include <cstdlib>
#include <cerrno>
#include <cstdio>
# include <string>
# include <fcntl.h>
# include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>
# include "serv.hpp"
# include "client.hpp"
# include "utils.hpp"

const int MAX_CLIENTS = 10;
const int BUFFER_SIZE = 1024;

class irc
{
    public :

        irc( void );
        irc( irc const & );
        irc & operator=( irc const & cp );
        ~irc( void );
        //--------------------Fonction-----------------------------------------------------------------------------------------

        int init(int argc, char** argv);
        int removeStringVector(std::vector<std::string>& myVector, const char* target);
        void copyVector(const std::vector<std::string> &src, std::vector<std::string> &dst);

        //------------------------VARIABLE---------------------------------------------------------------------------------------

        std::vector<std::string> line;
        std::vector<std::string> all_commands;
};

void    start_irc (int port, std::string pasword);

    template <class T>
void    printVector(std::vector<T>& myVector)
{
    std::cout << "Taille du vecteur : " << myVector.size() << "\n";
    for (long unsigned int i = 0; i < myVector.size(); i++)
        std::cout << "   value "  << i << " == " <<  myVector[i] << std::endl;
}
