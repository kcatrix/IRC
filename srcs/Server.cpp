#include "../includes/irc.hpp"

Server::Server (int port, std::string password) {
    users.reserve (10);
    _port = port;
    _password = password;
    init_address ();
    create_socket ();
}

void        Server::init_address (void) {
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = htonl (INADDR_ANY);
    _address.sin_port = htons (_port);
    bzero (_address.sin_zero, sizeof(_address.sin_zero));
    _addrlen = sizeof (_address);
}

void        Server::create_socket (void) {
    _server_fd = socket (AF_INET, SOCK_STREAM, 0);
    if (_server_fd < 0)
        print_error ("Server socket creation error");
    if (bind (_server_fd, (SOCKADDR*) &_address, sizeof(_address)) < 0)
        print_error ("Server socket binding error");
    if (listen (_server_fd, MAX_USERS) < 0)
        print_error ("Server socket listening error");
    fcntl(_server_fd, F_SETFL, O_NONBLOCK);
    std::cout << "Listening on port " << _port << std::endl;
}

int         Server::getFd (void) { return this->_server_fd; }

SOCKADDR_IN Server::getAddress (void) { return this->_address; }

int         Server::getAddressLength (void) { return this->_addrlen; }

std::string Server::getPassword (void) { return this->_password; }

Server::~Server (void) { 
    users.clear ();
    channels.clear ();
    close (_server_fd);
}
