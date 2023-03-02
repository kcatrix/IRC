#include "../includes/irc.hpp"

// ------------------------    Gestion entree infos users (a modifier pour coller au user protocol + J'ai rajoute une protect doublon en attendant) --------------------------------------

void    checkPassword (User* new_user, char* buffer, std::string password) {
        if (password.compare(buffer) == 0) {
            new_user->password = buffer;
            write(new_user->sd, "Enter your username: ", 21);
        }
        else
            write(new_user->sd, "Wrong password, try again: ", 27);
}

void    setUsername (User* new_user, char* buffer) {

        new_user->username = buffer;
        write(new_user->sd, "Enter your nickname: ", 21);
}

void    setNickname (User* new_user, char* buffer) {
    std::string message;

    new_user->nickname = buffer;
    message = "Welcome " + new_user->username + " " + new_user->nickname + " !\n";
    write(new_user->sd, message.c_str(), message.length());
    write(new_user->sd, "Enter a command: \n", 19);
}

int     getInfoUser (User* new_user, char* buffer, std::string password, std::vector<User> users) {
    removeInvisibleChars(buffer);
    if (new_user->password == "") {
        checkPassword (new_user, buffer, password);
        return 1;
    }
    else if (new_user->username == "") {
        if(checkdoublonuser(buffer, users, new_user->sd) == 1)
			return 1;
        setUsername (new_user, buffer);
        return 1;
    }
    else if (new_user->nickname == "") {
        if(checkdoublonnick(buffer, users, new_user->sd) == 1)
			return 1;
        setNickname (new_user, buffer);
        return 1;
    }
    else
        return 0;
}

void    createUser (int new_socket, VECTOR* users, int* max_sd, int* number_of_users) {
    User new_user (new_socket);
     if (*number_of_users >= MAX_USERS)
         exit(0); // a changer en fonction qui close toute les socket
     std::cout << "New user connected" << std::endl;
     fcntl(new_socket, F_SETFL, O_NONBLOCK);
     users->push_back (new_user);
     *max_sd = std::max (*max_sd, new_socket);
     (*number_of_users)++;
     write (new_socket, "Welcome to the server\n", 22);
     write (new_socket, "Enter the password\n", 19);
    
}
