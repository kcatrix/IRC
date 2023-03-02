#include "../includes/irc.hpp"

//  ----- a potentiellement modifier lors de la refonte du log de base du client -----------
void nick(int newsocket, char *buffer, std::vector<clien> *clients){ 

	char **buffspli = ft_split(buffer, ' ');
    for (ITERATOR it = clients->begin (); it != clients->end (); it++)
    {
        if ((*it).sd == newsocket)
		{
            if(buffspli[1] == NULL || (buffspli[1] != NULL && buffspli[2] != NULL))
                write(newsocket, "Votre entree n'est pas valide ! (nick <Nickname>)\n", 51);
            else
            {
			    if(checkdoublonnick(buffspli[1], *clients, newsocket) == 1)
				    return ;
			    (*it).nickname = buffspli[1];
                write(newsocket, "nick name :", 11);
                write (newsocket, (*it).nickname.c_str(), (*it).nickname.length());
            }
			// write(newsocket, client_tab[i].nickname.c_str(), client_tab[i].nickname.length());
		}
	}
	free_tab(buffspli);
}

