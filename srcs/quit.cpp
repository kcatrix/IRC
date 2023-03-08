#include "../includes/irc.hpp"

//  --------------- trouver la faille qui genere un probleme de select ---------------------
void quit(User executer)
{
    print_message (executer.sd, "Goodbye" + executer.nickname + " !\n");
    // kill(executer.sd, SIGINT); tentative d'arnaque échouer :(  l'envoi d'un ctrl+c au user ne fait absolument rien sans grande suprise cordialement
    close(executer.sd); //provoque une erreur de select
    return ;
    //users.erase(it); //fait segfault
}
