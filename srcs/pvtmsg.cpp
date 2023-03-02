#include "../includes/irc.hpp"

//  ---------------(fonctionne dans l'ensemble hors mask(pas implemente car manque d'info sans les channs) + mauvais sender car prob de socket de discord)--------------------------------------

void msg(int newsocket, char *buffer, std::vector<clien> clients) {

    //protect segfault
    char **buffspli = ft_split(buffer, ' ');
	std::string message;
    std::string messager;
	std::string display;

    for (ITERATOR it = clients.begin (); it != clients.end (); it++)
    {
        if ((*it).sd == newsocket)
			messager = (*it).username;
	}
    for (ITERATOR it = clients.begin (); it != clients.end (); it++)
    {
        if (buffspli[1] == (*it).username) //buffspli[1] == (*it).hostmask || 
        {
            if(buffspli[2])
                display = buffspli[2];
			for(int y = 3; buffspli[y] != NULL; y++)
				display = display + " " + buffspli[y];
			message = messager + ": " + display + '\n';
            write((*it).sd, message.c_str(), message.length() + 1);
        }
    }
    free_tab(buffspli);
}

