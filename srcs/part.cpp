#include "../includes/irc.hpp"

static void opequit (const User executer, CHANNEL_ITERATOR &to_quit) {
    for (STRING_ITERATOR it = to_quit->ope.begin (); it != to_quit->ope.end (); it++) {
        if (executer.nickname == *it) {
            to_quit->ope.erase (it);
            return;
        }
    }
}

void    part (User executer, std::vector<std::string> bufferSplit, Server& irc_server) {
    if (bufferSplit[1].empty () == 1)
        print_message (executer.sd, "Not enough parameters given.\n");
    else {
        CHANNEL_ITERATOR to_quit = findChannel (bufferSplit[1], irc_server);
        if (to_quit == irc_server.channels.end ()) {
            print_message (executer.sd, bufferSplit[1] + ": No such channel.\n");
            return;
        }
        else {
            USER_ITERATOR   quitter = executer.findUser (to_quit);
            if (quitter == to_quit->chan_users.end ())
                print_message (executer.sd, to_quit->channel_name + ": You're not on that channel\n");
            else {
                print_message (executer.sd, "You left the channel " + to_quit->channel_name + "\n");
                to_quit->chan_users.erase (quitter);
                opequit(executer, to_quit);
            }
        }
    }
}
