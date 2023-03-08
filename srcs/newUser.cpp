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
      //  print_message (new_user->sd, "Enter your nickname: ");
}

void    setNickname (User* new_user, char* buffer) {
    std::string message;

    new_user->nickname = buffer;
    print_message (new_user->sd, "Welcome to our server, " + new_user->nickname + " !\n");
    print_message (new_user->sd, "Type /help to see a list of the available commands.\n");
}

User    findUser (std::string nickname, USER_VECTOR users) {
    for (USER_ITERATOR user = users.begin (); user != users.end (); user++) {
        if (user->nickname == nickname)
            return *user;
    }
    return User ();
}

int     getInfoUser (User* new_user, char* buffer, std::string password, std::vector<User> users) {
    removeInvisibleChars(buffer);
    /*if (new_user->password == "") {
      checkPassword (new_user, buffer, password);
      return 1;
      }*/
    if (((new_user->nickname == "" and checkDuplicateNick(buffer, users) == 1) || new_user->x >= 1) && new_user->x != 1000) {
        User john = findUser (buffer, users);
        if(new_user->x == 0)
        {
            if (john.online == true) {
                print_message (new_user->sd, "Nickname already in use, please try another one\n");
                return 1;
            }
        }
        if (new_user->x == 1 || john.logInPwd != "") 
        {
            new_user->x++;
            if(new_user->x == 1)
            {
                new_user->nickname = buffer;
                print_message (new_user->sd, "Enter your password to log in: ");
                return 1;
            }
            User john = findUser(new_user->nickname, users);
            if (john.logInPwd == static_cast<std::string>(buffer)) 
            {
                print_message (new_user->sd, "Welcome back, " + john.nickname + ".\n");
                *new_user = john;
                new_user->x = 1000;
                return 1;
            }
            else {
                print_message (new_user->sd, "Wrong password. Try again: \n");
                return 1;
            }
            
        }
    }
    else if(new_user->x != 1000 && new_user->nickname == "")
    {
        setNickname (new_user, buffer);
        return 1;
    }
    (void)password;
    (void)users;
    /*if(isalpha(buffer[0]) == 0)
    {
        print_message (new_user->sd, "Error: Your nickname must start with alphabetic char \n");
        return 1;
    }
    //new_user->online = true;
    return 1;*/
    /* else if (new_user->username == "") {
       if(checkdoublonuser(buffer, users, new_user->sd) == 1)
       return 1;
       setUsername (new_user, buffer);
       return 1;
       }*/
    return 0;
}

void    createUser (int new_socket, USER_VECTOR* users, int* max_sd, int* number_of_users) {
    User new_user (new_socket);
     if (*number_of_users >= MAX_USERS)
         exit(0); // a changer en fonction qui close toute les socket
     std::cout << "A new user joined the server." << std::endl;
     fcntl(new_socket, F_SETFL, O_NONBLOCK);
     users->push_back (new_user);
     *max_sd = std::max (*max_sd, new_socket);
     (*number_of_users)++;
    print_message (new_user.sd, "Enter your nickname: ");
     //print_message (new_user.sd, "Enter the password to access this server.\n");
    
}
