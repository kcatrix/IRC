#include "../includes/irc.hpp"

static int	isOpe (STRING_VECTOR ope, User executer) {
	for (STRING_ITERATOR it = ope.begin (); it != ope.end (); it++) {
		if (*it == executer.nickname)
			return 1;
	}
	return 0;
}

static int isInChan (User executer, CHANNEL_ITERATOR &chan, STRING_VECTOR bufferSplit) {
	for (USER_ITERATOR it = chan->chan_users.begin (); it != chan->chan_users.end (); it++) {
		if (it->nickname == bufferSplit[2]) {
            chan->banned.push_back (it->nickname);
			std::string message = bufferSplit[3];
            for (int y = 4; bufferSplit[y].empty () == 0; y++)
                message = message + " " + bufferSplit[y];
			print_message (it->sd, "Banned from channel " + bufferSplit[1] + " by " + executer.nickname + ": " + message + "\n");
			for (STRING_ITERATOR itr = chan->ope.begin (); itr != chan->ope.end (); itr++) {
				if(it->nickname == *itr) {
					chan->ope.erase (itr);
					return 1;
				}
			}
			chan->chan_users.erase (it);
			return 1;
		}
	}
	return 0;
}

void    ban (User executer, STRING_VECTOR bufferSplit, Server& irc_server) {
    if (bufferSplit[1].empty () == 1 || bufferSplit[2].empty () == 1 || bufferSplit[3].empty () == 1)
        print_message (executer.sd, "Not enough parameters given.\n");
    else {
        CHANNEL_ITERATOR kick_from = findChannel (bufferSplit[1], irc_server);
        if (kick_from == irc_server.channels.end ()) {
            print_message (executer.sd, "The chann : " + bufferSplit[1] + " you tried to ban from doesn't exist\n");
        }
        else {
			if (isOpe (kick_from->ope, executer) == 0) {
				print_message (executer.sd, "You don't have enough rights to ban from the channel: " + bufferSplit[1] + "\n");
			}
			else if (bufferSplit[2] == executer.nickname) {
				print_message (executer.sd, "You cannot ban yourself!\n");
				return;
			}
			else {
				if (isInChan (executer, kick_from, bufferSplit) == 0)
					print_message (executer.sd, "No user: " + bufferSplit[2] + " in channel: " + bufferSplit[1] +  "\n");
			}
        }
	}
}

