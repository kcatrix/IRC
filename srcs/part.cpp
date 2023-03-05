#include "../includes/irc.hpp"

void    part (User executer, std::vector<std::string> bufferSplit, Server& irc_server) {
    if(bufferSplit[1].empty () == 1)
        print_message (executer.sd, "Not enough parameters given.\n");
    else {
        CHANNEL_ITERATOR to_quit = findChannel (bufferSplit[1], irc_server);
        if (to_quit == irc_server.channels.end ()) {
            print_message (executer.sd, bufferSplit[1] + ": No such channel.\n");
            return;
        }
 //       else
//            executer.removeUser (to_quit);
    }
}
