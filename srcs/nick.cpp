#include "../includes/irc.hpp"

//  ----- a potentiellement modifier lors de la refonte du log de base du user -----------
void nick(User& executer, std::vector<std::string> bufferSplit, std::vector<User> users){ 

    if(bufferSplit[1].empty () == 1 or (bufferSplit[1].empty () == 0 and bufferSplit[2].empty () == 0)) {
        print_message (executer.sd, "Votre entree n'est pas valide ! (/NICK <new nickname>)\n");
        return;
    }
    else {
        if(isalpha(bufferSplit[1][0]) == 0)
        {
            print_message (executer.sd, "Error: Your nickname must start with alphabetic char \n");
            return;
        }
        if(checkDuplicateNick(bufferSplit[1], users) == 1)
            return ;
        executer.nickname = bufferSplit[1];
        print_message (executer.sd, "new nickname: " + executer.nickname + "\n");
    }
    // write(newsocket, user_tab[i].nickname.c_str(), user_tab[i].nickname.length());
}

