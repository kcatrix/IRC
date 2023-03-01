#ifndef irc_HPP
# define irc_HPP

# include "clien.hpp"
# include "utils.hpp"
# include "Server.hpp"
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

void    start_irc (int port, std::string password);
void    getInfoClient(clien* new_client, char *buffer, std::string password);

template <class T>
void    printVector (std::vector<T>& myVector) {
    std::cout << "Taille du vecteur : " << myVector.size() << "\n";
    for (long unsigned int i = 0; i < myVector.size(); i++)
        std::cout << "   value "  << i << " == " <<  myVector[i] << std::endl;
}

#endif
