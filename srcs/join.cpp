#include "../includes/irc.hpp"

static int    checkNotBanned (User executer, STRING_VECTOR banned) {
    for (STRING_ITERATOR it = banned.begin (); it != banned.end (); it++) {
        if (executer.nickname == *it) {
            print_message (executer.sd, "You are banned from this channeln");
            return 1;
        }
    }
    return 0;
}

void    join (User executer, STRING_VECTOR bufferSplit, Server& irc_server) {
    if (bufferSplit[1].empty () == 1)
        print_message (executer.sd, "Not enough parameters given.\n");
    else {
        CHANNEL_ITERATOR to_join = findChannel (("#" + bufferSplit[1]), irc_server);
        if (to_join == irc_server.channels.end ())
            createChannel (executer, bufferSplit[1], irc_server);
        else {
            if (executer.findUser (to_join) == to_join->chan_users.end ()) {
                if(checkNotBanned (executer, to_join->banned) == 0) {
                    print_message (executer.sd, "You joined the channel " + to_join->channel_name + "\n");
                    to_join->chan_users.push_back (executer);
                }
            }
            else
                print_message (executer.sd, "You are already on the channel " + to_join->channel_name + "\n");
        }
    }
}
