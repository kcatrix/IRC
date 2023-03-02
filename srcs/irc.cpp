#include "../includes/irc.hpp"

#define VECTOR std::vector<clien>
#define ITERATOR std::vector<clien>::iterator




// ------------------------    Gestion doublons Nick / User --------------------------------------

int checkdoublonnick(char *tocheck, std::vector<clien> clients, int sd) //doublon nick
{
    for (ITERATOR it = clients.begin (); it != clients.end (); it++)
    {
		if((*it).nickname.compare(tocheck) == 0)
		{
			if(sd == (*it).sd)
				write(sd, "This is already your nickname !\n", 32);
			else
				write(sd, "nickname already in use, please try an other one\n", 49);
			return 1;
		}
	}
	return 0;
}

int checkdoublonuser(char *tocheck, std::vector<clien> clients, int sd) //doublon user
{
    for (ITERATOR it = clients.begin (); it != clients.end (); it++)
    {
		if((*it).nickname.compare(tocheck) == 0)
		{
			if(sd == (*it).sd)
				write(sd, "This is already your username !\n", 32);
			else
				write(sd, "username already in use, please try an other one\n", 49);
			return 1;
		}
	}
	return 0;
}


// ------------------------    Gestion entree infos users (a modifier pour coller au client protocol + J'ai rajoute une protect doublon en attendant) --------------------------------------

void    checkPassword (clien* new_client, char* buffer, std::string password) {
        if (password.compare(buffer) == 0) {
            new_client->password = buffer;
            write(new_client->sd, "Enter your username: ", 21);
        }
        else
            write(new_client->sd, "Wrong password, try again: ", 27);
}

void    setUsername (clien* new_client, char* buffer) {

        new_client->username = buffer;
        write(new_client->sd, "Enter your nickname: ", 21);
}

void    setNickname (clien* new_client, char* buffer) {
    std::string message;

    new_client->nickname = buffer;
    message = "Welcome " + new_client->username + " " + new_client->nickname + " !\n";
    write(new_client->sd, message.c_str(), message.length());
    write(new_client->sd, "Enter a command: \n", 19);
}

int     getInfoClient (clien* new_client, char* buffer, std::string password, std::vector<clien> clients) {
    removeInvisibleChars(buffer);
    if (new_client->password == "") {
        checkPassword (new_client, buffer, password);
        return 1;
    }
    else if (new_client->username == "") {
        if(checkdoublonuser(buffer, clients, new_client->sd) == 1)
			return 1;
        setUsername (new_client, buffer);
        return 1;
    }
    else if (new_client->nickname == "") {
        if(checkdoublonnick(buffer, clients, new_client->sd) == 1)
			return 1;
        setNickname (new_client, buffer);
        return 1;
    }
    else
        return 0;
}

void    createClient (int new_socket, VECTOR* clients, int* max_sd, int* number_of_clients) {
    clien new_client (new_socket);
     if (*number_of_clients >= MAX_CLIENTS)
         exit(0); // a changer en fonction qui close toute les socket
     std::cout << "New client connected" << std::endl;
     fcntl(new_socket, F_SETFL, O_NONBLOCK);
     clients->push_back (new_client);
     *max_sd = std::max (*max_sd, new_socket);
     (*number_of_clients)++;
     write (new_socket, "Welcome to the server\n", 22);
     write (new_socket, "Enter the password\n", 19);
    
}

//  ---------------------------------    Gestion PvtMsg (cas basique, reste a faire lors de la creation des channels)---------------------------------------------------------------------------
//  ---------------(fonctionne dans l'ensemble hors mask(pas implemente car manque d'info sans les channs) + mauvais sender car prob de socket de discord)--------------------------------------

void msg(int newsocket, char *buffer, std::vector<clien> clients) {

    //protect segfault
    char **buffspli = ft_split(buffer, ' ');
	std::string message;
    std::string messager;
	std::string display;

    for (ITERATOR it = clients.begin (); it != clients.end (); it++)
    {
        if ((*it).sd == newsocket)
			messager = (*it).username;
	}
    for (ITERATOR it = clients.begin (); it != clients.end (); it++)
    {
        if (buffspli[1] == (*it).username) //buffspli[1] == (*it).hostmask || 
        {
            if(buffspli[2])
                display = buffspli[2];
			for(int y = 3; buffspli[y] != NULL; y++)
				display = display + " " + buffspli[y];
			message = messager + ": " + display + '\n';
            write((*it).sd, message.c_str(), message.length() + 1);
        }
    }
    free_tab(buffspli);
}

//  ---------------------------------    Gestion Nick -------------------------------------- 
//  ----- a potentiellement modifier lors de la refonte du log de base du client -----------
void nick(int newsocket, char *buffer, std::vector<clien> *clients){ 

	char **buffspli = ft_split(buffer, ' ');
    for (ITERATOR it = clients->begin (); it != clients->end (); it++)
    {
        if ((*it).sd == newsocket)
		{
            if(buffspli[1] == NULL || (buffspli[1] != NULL && buffspli[2] != NULL))
                write(newsocket, "Votre entree n'est pas valide ! (nick <Nickname>)\n", 51);
            else
            {
			    if(checkdoublonnick(buffspli[1], *clients, newsocket) == 1)
				    return ;
			    (*it).nickname = buffspli[1];
                write(newsocket, "nick name :", 11);
                write (newsocket, (*it).nickname.c_str(), (*it).nickname.length());
            }
			// write(newsocket, client_tab[i].nickname.c_str(), client_tab[i].nickname.length());
		}
	}
	free_tab(buffspli);
}

//  ---------------------------------    Gestion Quit --------------------------------------
//  --------------- trouver la faille qui genere un probleme de select ---------------------
void quit(int newsocket, std::vector<clien> clients)
{
    std::string message;

    for (ITERATOR it = clients.begin (); it != clients.end (); it++)
    {
        if ((*it).sd == newsocket)
        {
            message = "Goodbye " + (*it).username + " " + (*it).nickname + " !\n";
            write(newsocket, message.c_str(), message.length());
			//close((*it).sd); //provoque une erreur de select
            //clients.erase(it); //fait segfault
        }
    }
}

//  ---------------------------------    Redir function  --------------------------------------

void redirectFonction(int newsocket, char *buffer, std::vector<clien>* client_tab, std::string password)
{
    (void)password;
    char **bufferspli = ft_split(buffer, ' ');
    if (strcmp(bufferspli[0], "pvtmsg") == 0)
        msg(newsocket, buffer, *client_tab);
    else if (strcmp(bufferspli[0], "nick") == 0)
        nick(newsocket, buffer, client_tab);
    else if (strcmp(buffer, "QUIT") == 0)
        quit(newsocket, *client_tab);
    // il faut d'abbord split le buffer sur l'espace pour avoir argv[0]
    
        // if (strcmp(buffer_spli, "/nick") == 0)
        //     nick(client_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/join") == 0)
        //     join(client_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/part") == 0)
        //     part(client_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/users") == 0)
        //     users(client_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/msg") == 0)
        //     msg(client_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/names") == 0)
        //     names(client_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/list") == 0)
        //     list(client_tab[newsocket], buffer);
        // else if (strcmp(buffer_spli, "/quit") == 0)
        //     quit(client_tab[newsocket], buffer);
        // else
        //     write(client_tab[newsocket].sd, "Command not found\n", 18);

    write(newsocket, "Redirect non fini \n", 19);
    free_tab(bufferspli);
}

void start_irc(int port, std::string password)
{
    Server    irc_server (port, password); 
    int       server_fd = irc_server.getFd ();
    int       address_length = irc_server.getAddressLength ();
    int       new_socket, activity, valread, sup = -1;
    int       max_sd = server_fd;
    int       number_of_clients = 0;
    ITERATOR  supp;
    fd_set    read_fds;
    char      buffer[BUFFER_SIZE];
    VECTOR    clients(0);
    SOCKADDR_IN   server_address = irc_server.getAddress ();

    while (true) {
        FD_ZERO(&read_fds);
        FD_SET(server_fd, &read_fds);
        for (ITERATOR it = clients.begin(); it != clients.end(); ++it)
            FD_SET((*it).sd, &read_fds);
        activity = select(max_sd + 1, &read_fds, NULL, NULL, NULL);
        if ((activity < 0) && (errno!=EINTR))
            print_error ("Select error");
        if (FD_ISSET(server_fd, &read_fds)) {
            if ((new_socket = accept(server_fd, (SOCKADDR*)&server_address, (socklen_t*)&address_length))<0)
                print_error ("Socket creation error");
			createClient (new_socket, &clients, &max_sd, &number_of_clients);
        }
        for (ITERATOR it = clients.begin(); it != clients.end(); it++) {
            memset(buffer, 0, BUFFER_SIZE);
            if (FD_ISSET((*it).sd, &read_fds)) {
                valread = read((*it).sd, buffer, BUFFER_SIZE);
                if (valread == 0) {
                    getpeername((*it).sd, (SOCKADDR*)&server_address, (socklen_t*)&address_length);
                    std::cout << "Client disconnected: " << inet_ntoa(server_address.sin_addr) << ":" \
                        << ntohs(server_address.sin_port) << std::endl; // clear clien non necessaire ?
                    number_of_clients--;
                    sup = (*it).sd;
                    supp = it;
                }
                else if (valread == -1 && errno == EAGAIN)
                    print_error ("Reading failure");
                else {
                    for (ITERATOR it = clients.begin (); it != clients.end (); it++)
                        if ((*it).sd == new_socket) {
							std::cout << "client socket =" <<  (*it).sd << "current socket " << new_socket << std::endl;
                            if (getInfoClient(it.base(), buffer, password, clients) == 0) // .base() pas risque ?
                                redirectFonction((*it).sd, buffer, &clients, password);
                        }
                    buffer[valread] = '\0';
                    getpeername((*it).sd, (SOCKADDR*)&server_address, (socklen_t*)&address_length);
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
