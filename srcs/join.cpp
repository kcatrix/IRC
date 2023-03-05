#include "../includes/irc.hpp"

void    join (User executer, std::vector<std::string> bufferSplit, Server& irc_server) {
    if(bufferSplit[1].empty () == 1)
        print_message (executer.sd, "Not enough parameters given.\n");
    else {
        CHANNEL_ITERATOR to_join = findChannel (bufferSplit[1], irc_server);
        if (to_join == irc_server.channels.end ())
            createChannel (executer, bufferSplit[1], irc_server);
        else
            executer.addUser (to_join);
    }
}
