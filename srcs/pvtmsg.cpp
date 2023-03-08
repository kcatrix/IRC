#include "../includes/irc.hpp"

//  ---------------(fonctionne dans l'ensemble hors mask(pas implemente car manque d'info sans les channs) + mauvais sender car prob de socket de discord)--------------------------------------

void msg(User executer, std::vector<std::string> bufferSplit, std::vector<User> users, Server& irc_server) {

    //protect segfault
    (void)irc_server;
	std::string message;
    if(bufferSplit[1].empty() == 1 || bufferSplit[2].empty() == 1 || bufferSplit[3].empty() == 1)
        return ;
    if (bufferSplit[1][0] != '#')
    {
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
                for(int y = 3; bufferSplit[y].empty () == 0; y++)
                    message = message + " " + bufferSplit[y];
                print_message ((*it).sd, "<" + executer.nickname + "> " + message + "\n");
            }
        }
    }
    else
    {
        CHANNEL_ITERATOR to_send = findChannel (bufferSplit[1], irc_server);
        for (USER_ITERATOR it = to_send->chan_users.begin (); it != to_send->chan_users.end (); it++)
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
            for(int y = 3; bufferSplit[y].empty () == 0; y++)
                message = message + " " + bufferSplit[y];
            print_message ((*it).sd, "<" + executer.nickname + "> " + message + "\n");
        }
    }
}

