#include "../includes/irc.hpp"

static int	isOpe(STRING_VECTOR ope, User executer) {
	for (STRING_ITERATOR it = ope.begin (); it != ope.end (); it++) {
		if (*it == executer.nickname)
			return 1;
	}
	return 0;
}



static int isInChan (User executer, CHANNEL_ITERATOR& chan, STRING_VECTOR bufferSplit) {
	for (USER_ITERATOR it = chan->chan_users.begin (); it != chan->chan_users.end (); it++) {
		if(it->nickname == bufferSplit[2]) {
            chan->ope.push_back(it->nickname);
			print_message (it->sd, "You were promoted to operator of channel " + bufferSplit[1] + " by " + executer.nickname + "\n");
			return 1;
		}
	}
	return 0;
}

void    op (User executer, STRING_VECTOR bufferSplit, Server& irc_server) {
    if (bufferSplit[1].empty () == 1 || bufferSplit[2].empty() == 1)
        print_message (executer.sd, "Not enough parameters given.\n");
    else {
        CHANNEL_ITERATOR chan_to_op = findChannel (bufferSplit[1], irc_server);
        if (chan_to_op == irc_server.channels.end ())
            print_message (executer.sd, "The chan: " + bufferSplit[1] + " doesn't exist\n");
        else {
            if (isOpe (chan_to_op->ope, executer) == 0)
				print_message (executer.sd, "You don't have enought right to op in the channel :" + bufferSplit[1] + "\n");
            else {
				if (isInChan (executer, chan_to_op, bufferSplit) == 0)
					print_message (executer.sd, "No user: " + bufferSplit[2] + " in channel: " + bufferSplit[1] +  "\n");
			}
        }
    }
}   
