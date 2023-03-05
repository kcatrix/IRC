#include "../includes/irc.hpp"
// ------------------------    Gestion entree infos users (a modifier pour coller au user protocol + J'ai rajoute une protect doublon en attendant) -------------------------------------- 
void    checkPassword (User* new_user, char* buffer, std::string password) {
        if (password.compare(buffer) == 0) {
            new_user->password = buffer;
            print_message (new_user->sd, "Enter your username: ");
        }
        else
            print_message (new_user->sd, "Wrong password, try again: ");
}

void    setUsername (User* new_user, char* buffer) {

        new_user->username = buffer;
        print_message (new_user->sd, "Enter your nickname: ");
}

void    setNickname (User* new_user, char* buffer) {
    std::string message;

    new_user->nickname = buffer;
    print_message (new_user->sd, "Welcome to our server, " + new_user->nickname + " !\n");
    print_message (new_user->sd, "Type /help to see a list of the available commands.\n");
}

int     getInfoUser (User* new_user, char* buffer, std::string password, std::vector<User> users) {
    removeInvisibleChars(buffer);
/*    if (new_user->password == "") {
        checkPassword (new_user, buffer, password);
        return 1;
    }
    else if (new_user->username == "") {
        if(checkdoublonuser(buffer, users, new_user->sd) == 1)
			return 1;
        setUsername (new_user, buffer);
        return 1;
    }
    else*/ if (new_user->nickname == "") {
        //if(checkDuplicateNick(buffer, users, new_user->sd) == 1)
		//	return 1;
        (void)password;
        (void)users;
      //  print_message (new_user->sd, "Enter your nickname: ");
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
     std::cout << "A new user joined the server." << std::endl;
     fcntl(new_socket, F_SETFL, O_NONBLOCK);
     users->push_back (new_user);
     *max_sd = std::max (*max_sd, new_socket);
     (*number_of_users)++;
     //print_message (new_user.sd, "Enter the password to access this server.\n");
    
}
