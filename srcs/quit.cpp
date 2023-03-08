#include "../includes/irc.hpp"

//  --------------- trouver la faille qui genere un probleme de select ---------------------
void quit(User& executer)
{
    print_message (executer.sd, "Goodbye" + executer.nickname + " !\n");
    close(executer.sd); //provoque une erreur de select
    executer.sd = 0;
    return ;
}
