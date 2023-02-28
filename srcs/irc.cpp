#include "../includes/irc.hpp"

irc::irc( void ){ return; }

irc::~irc( void ){ return; }

irc::irc( irc const & ){ return; }

irc & irc::operator=( irc const & cp )
{
	this->line = cp.line;
	this->all_commands = cp.all_commands;
	return *this;
}

int irc::removeStringVector(std::vector<std::string>& myVector, const char* target)
{
	int lenght = myVector.size();
	for (int i = 0; i < lenght; ++i) 
	{
    	if (myVector[i] == target) 
		{
      		myVector.erase(myVector.begin() + i);
			return (0);
      		break;
		}
	}
	std::cout << "not find \n"; 
	return(1);
}

void irc::copyVector(const std::vector<std::string> &src, std::vector<std::string> &dst)
{
    for (long unsigned int i = 0; i < src.size(); i++)
    {
        dst.push_back(src[i]);
    }
}

void    start_irc (int port, std::string password) {
    int new_socket, activity, valread, sd, sup = -1;
    int max_sd;
    std::vector<int>::iterator supp;
    fd_set read_fds;
    char buffer[BUFFER_SIZE] = {0};
    std::string message = "Please enter your username\n";
    std::vector<int> clients;
    Server      irc_server (port, password);
    int         server_fd = irc_server.getFd ();
    int         address_length = irc_server.getAddressLength ();
    SOCKADDR_IN server_address = irc_server.getAddress ();

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
            if ((new_socket = accept(server_fd, (SOCKADDR*)&server_address, (socklen_t*)&address_length))<0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            // Set the new client socket to non-blocking mode
            fcntl(new_socket, F_SETFL, O_NONBLOCK);
            clients.push_back(new_socket);
            printf("New client connected\n");
            //clien *client_tab = new clien("john", "doe"); 


        }
        for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); it++) {
            sd = *it;

            if (FD_ISSET(*it, &read_fds)) {
                // Receive data from the client
                valread = read(*it, buffer, BUFFER_SIZE);
                if (valread == 0) {
                    // Client disconnected
                    getpeername(sd, (struct sockaddr*)&server_address, (socklen_t*)&address_length);
                    printf("Client disconnected: %s:%d\n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));
                    sup = *it;
                    supp = it;
                }
                else if (valread == -1 && errno == EAGAIN) {
                    std::cout << "passe\n";
                    // No data available yet
                    continue;
                }
                else {

                    // send(it, "", strlen(buffer), 0);
                    buffer[valread] = '\0';
                    getpeername(sd, (SOCKADDR*)&server_address, (socklen_t*)&address_length);
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
}
