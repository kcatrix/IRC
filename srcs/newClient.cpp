#include "../includes/irc.hpp"

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
