#pragma once

# include "irc.hpp"

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
const int MAX_USERS = 10;
const int BUFFER_SIZE = 1024;

class Server {

    public:

        Server (int port, std::string password);
        Server (const Server& cpy) : _port (cpy._port), _server_fd (cpy._server_fd), _addrlen (cpy._addrlen), \
                                     _address (cpy._address), _password (cpy._password) { }

        virtual ~Server (void);

        std::vector<User>           users;
        std::vector<Channel>        channels;
        std::vector<std::string>    commands_list;

        int         getFd (void);
        int         getAddressLength (void);
        SOCKADDR_IN getAddress (void);
        std::string getPassword (void);

    private:

        Server (void) { }
        Server& operator= (const Server& rhs) {
            (void)rhs;
            return *this;
        }

        int         _port;
        int         _server_fd;
        int         _addrlen;
        SOCKADDR_IN _address;
        std::string _password;

        void    init_address (void);
        void    create_socket (void);
        void    assignCommands (std::vector<std::string>& commands_list);
};
