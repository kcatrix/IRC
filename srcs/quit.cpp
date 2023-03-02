#include "../includes/irc.hpp"

//  --------------- trouver la faille qui genere un probleme de select ---------------------
void quit(clien executer)
{
    std::string message;

    message = "Goodbye " + executer.username + " " + executer.nickname + " !\n";
    write(executer.sd, message.c_str(), message.length());
    //close((*it).sd); //provoque une erreur de select
    //clients.erase(it); //fait segfault
}
