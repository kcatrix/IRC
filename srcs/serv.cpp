#include "../includes/serv.hpp"
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//conseil jé utiliser select

int run(irc *irc)
{
	(void) irc;
  std::vector<int> client_sockets;
  //init var serveur socket
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Créez un tableau de sockets à surveiller.
  fd_set read_fds;
  int max_fd;

  // Boucle infinie
  while (true) {
    FD_ZERO(&read_fds);
    FD_SET(server_socket, &read_fds);
    max_fd = server_socket;

    // Ajoutez ici les sockets clients connectés existants pour être surveillés également.
    for (unsigned int i = 0; i < client_sockets.size(); i++) {
      FD_SET(client_sockets[i], &read_fds);
      max_fd = std::max(max_fd, client_sockets[i]);
    }

    // Utilisez la fonction `select` pour surveiller les sockets.
    int activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
    if (activity < 0) {
      // Gestion des erreurs
    } else if (FD_ISSET(server_socket, &read_fds)) {
      int client_socket = accept(server_socket, NULL, NULL);
      // Ajoutez le nouveau socket client à la liste des sockets clients connectés.
      client_sockets.push_back(client_socket);
    } else {
      // Gérez les activités sur les sockets clients existants.
      for (unsigned int i = 0; i < client_sockets.size(); i++) {
        if (FD_ISSET(client_sockets[i], &read_fds)) {
        }
      }
    }
	int port = 8080;
	const char *address = "127.0.0.1";

	//Connection au serveur
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(address);
	int connection_status = connect(sock, (struct sockaddr *) &server, sizeof(server));

	if(connection_status == -1) {
	    std::cout << "Error connecting to server" << std::endl;
	} else {
	    std::cout << "Connected to server" << std::endl;
	}
  }

  return 0;
}
