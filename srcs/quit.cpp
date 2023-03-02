#include "../includes/irc.hpp"

//  --------------- trouver la faille qui genere un probleme de select ---------------------
void quit(User executer)
{
    std::string message;

    message = "Goodbye " + executer.username + " " + executer.nickname + " !\n";
    write(executer.sd, message.c_str(), message.length());
    // kill(executer.sd, SIGINT); tentative d'arnaque échouer :(  l'envoi d'un ctrl+c au user ne fait absolument rien sans grande suprise cordialement
    close(executer.sd); //provoque une erreur de select
    return ;
    //users.erase(it); //fait segfault
}
