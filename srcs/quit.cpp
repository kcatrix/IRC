#include "../includes/irc.hpp"

//  --------------- trouver la faille qui genere un probleme de select ---------------------
void quit(clien executer)
{
    std::string message;

    message = "Goodbye " + executer.username + " " + executer.nickname + " !\n";
    write(executer.sd, message.c_str(), message.length());
    // kill(executer.sd, SIGINT); tentative d'arnaque échouer :(  l'envoi d'un ctrl+c au client ne fait absolument rien sans grande suprise cordialement
    close(executer.sd); //provoque une erreur de select
    return ;
    //clients.erase(it); //fait segfault
}
