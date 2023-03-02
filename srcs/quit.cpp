#include "../includes/irc.hpp"

//  --------------- trouver la faille qui genere un probleme de select ---------------------
void quit(int newsocket, std::vector<clien> clients)
{
    std::string message;

    for (ITERATOR it = clients.begin (); it != clients.end (); it++)
    {
        if ((*it).sd == newsocket)
        {
            message = "Goodbye " + (*it).username + " " + (*it).nickname + " !\n";
            write(newsocket, message.c_str(), message.length());
			//close((*it).sd); //provoque une erreur de select
            //clients.erase(it); //fait segfault
        }
    }
}
