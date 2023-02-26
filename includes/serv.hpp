#ifndef serv_HPP
# define serv_HPP
#include "irc.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

int client(irc *irc);
//int server(irc *irc);

class Server {

    public:

        Server (int port);
        virtual ~Server (void);

        void    init_address (void);
        void    create_socket (void);
        void    loop (void);

    private:

        Server (void) { }
        Server (const Server& cpy) { (void)cpy; }
        Server& operator= (const Server& rhs) {
            (void)rhs; 
            return *this;
        }

        int         _port;
        int         _server_fd;
        int         _addrlen;
        SOCKADDR_IN _address;
};

#endif
