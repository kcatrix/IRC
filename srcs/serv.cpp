#include "../includes/serv.hpp"
#include "../includes/clien.hpp"
#include "msg.cpp"
#include "../includes/utils.hpp"
#include <sys/time.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <cerrno>
#include <cstdio>
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
  irc->client_tab_iterator = 0;
  int server_fd, new_socket, activity, valread, sd, sup = -1;
  int max_sd, addrlen;
  clien client_tab[MAX_CLIENTS];
  std::vector<int>::iterator supp;
  struct sockaddr_in address;
  fd_set read_fds;
  char buffer[BUFFER_SIZE];
  std::vector<int> clients;
   address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(irc->port);
   
    //--------------------VARIABLE-----------------------------------------------
   
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
      perror("socket failed");
      exit(EXIT_FAILURE);
  }
   
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
      perror("bind failed");
      exit(EXIT_FAILURE);
  }

  std::cout << "Listening on port " << irc->port << std::endl;
   
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
          if (CheckClientExiste(client_tab, new_socket) == 0)
          {
             if (irc->client_tab_iterator >= MAX_CLIENTS)
                exit(0); // a changer en fonction qui close toute les socket
             write(new_socket, "Welcome to the server\n", 22);
             write(new_socket, "Enter the password\n", 19);
             client_tab[irc->client_tab_iterator].sd = new_socket;
             irc->client_tab_iterator++;
          }
          
      }
      
      for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); it++) {
          sd = *it;
          memset(buffer, 0, BUFFER_SIZE);
          if (FD_ISSET(*it, &read_fds)) {
              // Receive data from the client
              valread = read(*it, buffer, BUFFER_SIZE);
              if (valread == 0) {
                  // Client disconnected
                  getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                  printf("Client disconnected: %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                  sup = *it;
                  supp = it;
              }
              else if (valread == -1 && errno == EAGAIN) {
                  perror("fatal error on client socket");
                  exit(EXIT_FAILURE);
              }
              else {
                if (checkInfoClient(*it, buffer, client_tab, irc ) == 0)
                    redirectFonction(*it, buffer, client_tab, irc);    
                  getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                  std::cout << "buffer = " << buffer << std::endl;
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

void removeInvisibleChars(char* str)
{
    int i = 0;
    while (str[i])
        i++;
    i--;
    str[i] = '\0';
}

std::string generateHostMask(std::string nickname, std::string username, std::string hostname)
{
    return nickname + "!~" + username + "@" + hostname;
}

int checkInfoClient(int new_socket, char *buffer, clien *client_tab, irc *irc)
{
    removeInvisibleChars(buffer);
    std::string message;
    std::string commande;

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (client_tab[i].sd == new_socket)
        {
            if (client_tab[i].password == "")
            {
                if (irc->mdp.compare(buffer) == 0)
                {
                    client_tab[i].password = buffer;
                    write(new_socket, "Enter your username: ", 21);
                    return (1);
                }
                else
                {
                    write(new_socket, "Wrong password, try again: ", 27);
                    return (1);
                }
                std::cout << "Pwdpass" << std::endl;
            }
            else if (client_tab[i].username == "")
            {
                std::cout << "Usernamepass" << std::endl;
                client_tab[i].username = buffer;
                write(new_socket, "Enter your nickname: ", 21);
                return(1);
            }
            else if (client_tab[i].nickname == "")
            {
                std::cout << "Nicknamepass" << std::endl;
                // Remove any newline or carriage return characters from the end of the buffer
                int len = strlen(buffer);
                while (len > 0 && (buffer[len-1] == '\n' || buffer[len-1] == '\r')) {
                    buffer[--len] = '\0';
                }
                client_tab[i].nickname = buffer;
                message = "Welcome " + client_tab[i].username + " " + client_tab[i].nickname + " !\n";
                write(new_socket, message.c_str(), message.length());
				client_tab[i].hostname = "irc.domain"; // potentiellement a modifier (initialisation de domaine pour tous les clients)
				client_tab[i].hostmask = generateHostMask(client_tab[i].nickname, client_tab[i].username, client_tab[i].hostname); // generation hostmask sans ident 
				//client_tab[i].hostmask = generateHostMask(client_tab[i].nickname, client_tab[i].username, client_tab[i].hostname); // generation hostmask avec ident
                commande = "Enter a command: \n" ;
                write(new_socket, commande.c_str(), commande.length());
                return(1);
            }
        }
    }
    std::cout << "COUCOU " << std::endl;
    return (0);
}

int CheckClientExiste(clien *client_tab, int new_socket)
{
    std::string message;
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (client_tab[i].sd == new_socket)
        {
            write(new_socket, "Welcome back\n", 13);
            if (client_tab[i].password == "")
            {
                write(new_socket, "Enter the password\n", 19);
                return 1;
            }
            else if (client_tab[i].username == "")
            {
                write(new_socket, "Enter your username: ", 21);
                return 1;
            }
            else if (client_tab[i].nickname == "")
            {
                write(new_socket, "Enter your nickname: ", 21);
                return 1;
            }
            else
                write(new_socket, "Enter a command: \n", 18);
            return 1;
        }
    }
    return 0;
} 


void msg(int newsocket, char *buffer, clien *client_tab, irc *irc)
{
    // // char *check;
    // // char *check2 = strdup(buffer);
	// // check = strtok(check2, " ");
    // // check = strtok(check2, " ");
    // std::cout << check << std::endl;
	(void) irc;
	int ID;
	// for(int i = 0; i < MAX_CLIENTS; i++)
	// {
	// 	getline(buffer, stock[i], " "))	
	// }
    char **buffspli = ft_split(buffer, ' ');
	for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (client_tab[i].sd == newsocket)
			ID = i;
	}
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
        if (buffspli[1] == client_tab[i].hostname || buffspli[1] == client_tab[i].username)
        {
            // check = strtok(buffer, " ");
            // while(check != NULL)
            //     check = strtok(buffer, " ");
            write(client_tab[i].sd, buffspli[2], strlen(buffspli[2]));
        }
    }
}

void redirectFonction(int newsocket, char *buffer, clien *client_tab, irc *irc)
{
	// char *check;
    // check = strtok(buffer, " ");
    char **bufferspli = ft_split(buffer, ' ');
	if (strcmp(bufferspli[0], "pvtmsg") == 0)
        msg(newsocket, buffer, client_tab, irc);
    // if (strcmp(buffer, "/nick") == 0)
    //     nick(newsocket, buffer, client_tab, irc);
    // else if (strcmp(buffer, "/list") == 0)
    //     list(newsocket, buffer, client_tab, irc);
    // else if (strcmp(buffer, "/join") == 0)
    //     join(newsocket, buffer, client_tab, irc);
    // else if (strcmp(buffer, "/part") == 0)
    //     part(newsocket, buffer, client_tab, irc);
    // else if (strcmp(buffer, "/users") == 0)
    //     users(newsocket, buffer, client_tab, irc);
    // else if (strcmp(buffer, "/quit") == 0)
    //     quit(newsocket, buffer, client_tab, irc);
    // else if (strcmp(buffer, "/help") == 0)
    //     help(newsocket, buffer, client_tab, irc);
    // else
    //     write(newsocket, "Command not found\n", 18);
    //send(newsocket, "test1", 5, 0);
	//delete stock[];
}
