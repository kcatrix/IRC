#ifndef serv_HPP
# define serv_HPP
#include "irc.hpp"
#include "clien.hpp"

int client(irc *irc);
int server(irc *irc);
void checkInfoClient(int new_socket, char *buffer, clien *client_tab, irc *irc);

#endif
