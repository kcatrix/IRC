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
  int server_fd, new_socket, activity, valread, sd, sup = -1;
  int max_sd, addrlen;
  std::vector<int>::iterator supp;
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
  address.sin_port = htons(8083);
   
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
      
      for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); it++) {
          sd = *it;
          if (FD_ISSET(*it, &read_fds)) {
              // Receive data from the client
              valread = read(*it, buffer, BUFFER_SIZE);
              if (valread == 0) {
                  std::cout << "passe\n";
                  // Client disconnected
                  getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                  printf("Client disconnected: %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                  sup = *it;
                  supp = it;
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
      if (sup > 0){
        close(sup);
        clients.erase(supp);
        sup = -1;
      }
  }

    return 0;

}
