#ifndef serv_HPP
# define serv_HPP
#include "irc.hpp"
#include "clien.hpp"

int client(irc *irc);
int server(irc *irc);
int	 checkInfoClient(int new_socket, char *buffer, clien *client_tab, irc *irc);
void redirectFonction(int newsocket, char *buffer, clien *client_tab, irc *irc);
int	 CheckClientExiste(clien *client_tab, int new_socket);

#endif
