#include "../includes/irc.hpp"

//  ---------------(fonctionne dans l'ensemble hors mask(pas implemente car manque d'info sans les channs) + mauvais sender car prob de socket de discord)--------------------------------------

void msg(User executer, std::vector<std::string> bufferSplit, std::vector<User> users) {

    //protect segfault
	std::string message;

    for (USER_ITERATOR it = users.begin (); it != users.end (); it++)
    {
        if (bufferSplit[1] == (*it).nickname) //buffspli[1] == (*it).hostmask || 
        {
            std::cout << "away == " << (*it).away << std::endl; 
            if ((*it).away == true )// ne fonctionne pas car pas de away == false meme aprés fonction away           
            {
                message = (*it).away_message + '\n';
                print_message ((*it).sd, message);
                return ;
            } 
            if(bufferSplit[2].empty () == 0)
                message = bufferSplit[2];
			for(int y = 3; bufferSplit[y].empty () == 1; y++)
				message = message + " " + bufferSplit[y];
            print_message ((*it).sd, "<" + executer.nickname + ">" + message + "\n");
        }
    }
}

