#include "../includes/irc.hpp"

//  ---------------(fonctionne dans l'ensemble hors mask(pas implemente car manque d'info sans les channs) + mauvais sender car prob de socket de discord)--------------------------------------

void msg(User executer, char *buffer, std::vector<User> users) {

    //protect segfault
    char **buffspli = ft_split(buffer, ' ');
	std::string message;
    std::string messager = executer.username;
	std::string display;

    for (ITERATOR it = users.begin (); it != users.end (); it++)
    {
        if (buffspli[1] == (*it).username) //buffspli[1] == (*it).hostmask || 
        {
            std::cout << "message envoyé a " << (*it).username << std::endl;

            std::cout << "away == " << (*it).away << std::endl; 
            if ((*it).away == true )// ne fonctionne pas car pas de away == false meme aprés fonction away           
            {
                message = (*it).away_message + '\n';
                write(executer.sd, message.c_str(), message.length() + 1);
                free_tab(buffspli);
                return ;
            } 
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

