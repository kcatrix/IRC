#include "../includes/irc.hpp"

void    printNames (int sd, std::string channel_name, Server& irc_server) {
    CHANNEL_ITERATOR    channel = findChannel (channel_name, irc_server);
    
    if (channel != irc_server.channels.end ()) {
        print_message (sd, "Users present on the channel " + channel->channel_name + ":\n");
        for (USER_ITERATOR current_user = channel->chan_users.begin (); current_user != channel->chan_users.end (); current_user++)
            print_message (sd, current_user->nickname + "\n");
    }
}

void    names (User executer, STRING_VECTOR bufferSplit, Server& irc_server) {
    if(bufferSplit[1].empty () == 1)
        print_message (executer.sd, "Not enough parameters given.\n");
    else {
        for (STRING_ITERATOR it = bufferSplit.begin () + 1; it != bufferSplit.end (); it++)
            printNames (executer.sd, *it, irc_server);
    }
}
