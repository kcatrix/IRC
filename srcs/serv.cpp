#include "../includes/serv.hpp"
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

//conseil jé utiliser select

int server(irc *irc)
{
	(void) irc;
  int nb_max_client = 3;
  //init var serveur socket
  int socketServer;
  socketServer = socket(AF_INET, SOCK_STREAM, 0); //AF_inet (ipv4) Sock_stream (socket tcp)
  struct sockaddr_in addrServer;
  addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
  addrServer.sin_family = AF_INET;
  addrServer.sin_port = htons(3000);

  //connecter le serveur 
  bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer));
  std::cout << "bind : " << socketServer << "\n";

  listen(socketServer, nb_max_client);
  std::cout << "listen\n";

  //utiliser select pour gérer plusieur client simultanément 

  fd_set readfs;
  while(1)
  {
    int max_fd = socketServeur;
    //On vide l'ensemble de lecture et on lui ajoute 
    //la socket serveur
    FD_ZERO(&readfs);
    FD_SET(socketServer, &readfs);
    int activity = select(max_fd + 1, &readfs, NULL, NULL, NULL);
    if (activity == -1)
        exit(0);
    if (activity == 0)
      std::cout << "Aucune activité dans les 10 secondes\n";
    else
    {
      if (FD_ISSET(socketServer, &readfs))
      {
        SOCKADDR_IN csin;
        unsigned int crecsize = sizeof csin;
        int socketClient = accept(socketServer, (SOCKADDR *) &csin, &crecsize);
        close(socketClient);
        std::cout << "Un client s'est connecte\n";
      }
    }
  }
 /* struct sockaddr_in addrClient;
  socklen_t csize = sizeof(addrClient);
  int socketClient = accept(socketServer, (struct sockaddr *)&addrClient , &csize);  
  std::cout << "accept\n";

  std::cout << "client : " << socketClient << "/n";


  close(socketClient);
  close(socketServer);

  std::cout << "close\n";
*/
  return(0);
}

int client(irc *irc)
{
  (void) irc;
  std::string env;
  int socketClient;
  socketClient = socket(AF_INET, SOCK_STREAM, 0); //AF_inet (ipv4) Sock_stream (socket tcp)
  struct sockaddr_in addrClient;
  addrClient.sin_addr.s_addr = inet_addr("127.0.0.1");
  addrClient.sin_family = AF_INET;
  addrClient.sin_port = htons(3000);
  connect(socketClient, (const struct sockaddr *)&addrClient, sizeof(addrClient));
  std::cout << "connecté\n";

  std::cout << "env = " << env << "\n";

  close(socketClient);
  return(0);
}

 /*/ // Créez un tableau de sockets à surveiller.
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
*/