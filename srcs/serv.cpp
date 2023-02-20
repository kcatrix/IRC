#include "../includes/serv.hpp"
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
const int MAX_CLIENTS = 10;
const int BUFFER_SIZE = 1024;

//conseil jé utiliser select

int server(irc *irc)
{
  (void) irc;
  int server_fd, new_socket, activity, valread, sd;
  int max_sd, addrlen;
  struct sockaddr_in address;
  fd_set read_fds;
  char buffer[BUFFER_SIZE] = {0};
  std::vector<int> clients;
   
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
      perror("socket failed");
      exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);
   
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
      perror("bind failed");
      exit(EXIT_FAILURE);
  }
   
  if (listen(server_fd, MAX_CLIENTS) < 0) {
      perror("listen");
      exit(EXIT_FAILURE);
  }
  addrlen = sizeof(address);
  // Set the server socket to non-blocking mode
  fcntl(server_fd, F_SETFL, O_NONBLOCK);
  while (true) {
      FD_ZERO(&read_fds);
      FD_SET(server_fd, &read_fds);
      max_sd = server_fd;
       
      for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
          sd = *it;
          FD_SET(sd, &read_fds);
          if (sd > max_sd) max_sd = sd;
      }
      activity = select(max_sd + 1, &read_fds, NULL, NULL, NULL);
    
      if ((activity < 0) && (errno!=EINTR)) {
          printf("select error");
      }
      
      if (FD_ISSET(server_fd, &read_fds)) {
          if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
              perror("accept");
              exit(EXIT_FAILURE);
          }
           
          // Set the new client socket to non-blocking mode
          fcntl(new_socket, F_SETFL, O_NONBLOCK);
          clients.push_back(new_socket);
          printf("New client connected\n");
      }
       
      for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
          sd = *it;
          if (FD_ISSET(sd, &read_fds)) {
              // Receive data from the client
              valread = read(sd, buffer, BUFFER_SIZE);
              if (valread == 0) {
                  // Client disconnected
                  getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                  printf("Client disconnected: %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                  close(sd);
                  clients.erase(it);
              }
              else if (valread == -1 && errno == EAGAIN) {
                  // No data available yet
                  continue;
              }
              else {
                  buffer[valread] = '\0';
                  getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                  std::cout << buffer << std::endl;
              }
          }
      }
  }

    return 0;

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
  std::string response;

  while (response != "exit")
  {
    // Receive a message from the server
    char buffer[1024] = {0};
    memset(buffer, 0, sizeof(buffer));
    recv(socketClient, buffer, 1024, 0);
    std::cout << "Received message from server: " << buffer << "\n";

    // Prompt the user for a response
    std::string response;
    std::cout << "Enter your response: ";
    std::getline(std::cin, response);
    // Send the response back to the server
    send(socketClient, response.c_str(), response.length(), 0);
  }
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