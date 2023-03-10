#include "../includes/irc.hpp"

static int	isOpe (STRING_VECTOR ope, User executer) {
	for (STRING_ITERATOR it = ope.begin (); it != ope.end (); it++) {
		if(*it == executer.nickname)
			return 1;
	}
	return 0;
}

static int	isInChan (User executer, CHANNEL_ITERATOR &chan, STRING_VECTOR bufferSplit, Server& irc_server) {
    for (STRING_ITERATOR itr = chan->banned.begin (); itr != chan->banned.end (); itr++) {
        if(*itr == bufferSplit[2]) {
            chan->banned.erase (itr);
            for (USER_ITERATOR it = irc_server.users.begin (); it != irc_server.users.end (); it++) {
                if (it->nickname == *itr) {
                    std::string message = bufferSplit[3];
                    for (int y = 4; bufferSplit[y].empty () == 0; y++)
                        message = message + " " + bufferSplit[y];
                    print_message (it->sd, "Unbanned from channel " + bufferSplit[1] + " by " + executer.nickname + ": " + message + "\n");
                    return 1;
                }
            }
        }
    }
	return 0;
}


void    unban (User executer, STRING_VECTOR bufferSplit, Server& irc_server) {
    if (bufferSplit[1].empty () == 1 || bufferSplit[2].empty () == 1 || bufferSplit[3].empty () == 1)
        print_message (executer.sd, "Not enough parameters given.\n");
    else {
        CHANNEL_ITERATOR kick_from = findChannel (bufferSplit[1], irc_server);
        if (kick_from == irc_server.channels.end ())
            print_message (executer.sd, "The chan: " + bufferSplit[1] + " doesn't exist\n");
        else {
			if (isOpe (kick_from->ope, executer) == 0)
				print_message (executer.sd, "You don't have enough rights to unban from the channel: " + bufferSplit[1] + "\n");
			else if (bufferSplit[2] == executer.nickname) {
				print_message (executer.sd, "You cannot unban yourself!\n");
				return;
			}
			else
				isInChan (executer, kick_from, bufferSplit, irc_server);
        }
	}
}
