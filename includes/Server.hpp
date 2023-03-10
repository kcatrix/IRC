#pragma once

# include "irc.hpp"

class Server {

    public:

        Server (const int port, const std::string password);
        Server (const Server& cpy) : _port (cpy._port), _server_fd (cpy._server_fd), _addrlen (cpy._addrlen), \
                                     _address (cpy._address), _password (cpy._password) { }

        virtual ~Server (void);

        USER_VECTOR     users;
        CHANNEL_VECTOR  channels;
        STRING_VECTOR	commands_list;

        int         getFd (void) const;
        int         getAddressLength (void) const;
        SOCKADDR_IN getAddress (void) const;
        std::string getPassword (void) const;

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
