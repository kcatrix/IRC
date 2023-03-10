#include "../includes/irc.hpp"


static int	isOpe (STRING_VECTOR ope, User executer) {
	for (STRING_ITERATOR it = ope.begin (); it != ope.end (); it++) {
		if (*it == executer.nickname)
			return 0;
	}
	return  1;
}

static int    checkisUser (User executer, STRING_VECTOR bufferSplit, Server& irc_server, CHANNEL_ITERATOR &chan) {
    for (USER_ITERATOR it = irc_server.users.begin (); it != irc_server.users.end (); it++) {
        if(it->nickname == bufferSplit[2]) {
            std::string message = bufferSplit[3];
            for (int y = 4; bufferSplit[y].empty () == 0; y++)
                message = message + " " + bufferSplit[y];
            print_message (it->sd, "Your were invited to the channel " + bufferSplit[1] + " by " + executer.nickname + ": " + message + "\n");
            chan->chan_users.push_back(*it);
            return(0);
        }
    }
    print_message (executer.sd, "The user " + bufferSplit[2] + " doesn't exist\n");
    return 1;
}

static int    checkisBanned (User executer, STRING_VECTOR banned, STRING_VECTOR bufferSplit) {
    for (STRING_ITERATOR it = banned.begin (); it != banned.end (); it++) {
        if( bufferSplit[2] == *it) {
            print_message (executer.sd, "The user " + bufferSplit[2] + " is banned from this channel");
            return 1;
        }
    }
    return 0;
}

static int isInChan (User executer, CHANNEL_ITERATOR &chan, STRING_VECTOR bufferSplit, Server& irc_server) {
	for (USER_ITERATOR it = chan->chan_users.begin (); it != chan->chan_users.end (); it++) {
		if (it->nickname == bufferSplit[2]) {
            if (executer.nickname == it->nickname)
                print_message (executer.sd, "You cannot invite yourself in a channel\n");
            else
			    print_message (executer.sd, "The User you tried to invite is already in the channel\n");
			return 1;
        }
	}
    if (checkisBanned (executer, chan->banned, bufferSplit) == 1)
        return 1;
    if (checkisUser (executer, bufferSplit, irc_server, chan) == 1)
        return 1;
	return 0;
}

void    invite (User executer, STRING_VECTOR bufferSplit, Server& irc_server) {

    if (bufferSplit[1].empty () == 1 || bufferSplit[2].empty () == 1 || bufferSplit[3].empty () == 1)
        print_message (executer.sd, "Not enough parameters given.\n");
    else {
        CHANNEL_ITERATOR invite_to = findChannel (bufferSplit[1], irc_server);
        if (invite_to == irc_server.channels.end ())
            print_message (executer.sd, "The chan: " + bufferSplit[1] + " doesn't exist\n");
        else {
			if (isOpe (invite_to->ope, executer) == 1)
				print_message (executer.sd, "You don't have enough rights to invite in the channel :" + bufferSplit[1] + "\n");
			else
                isInChan (executer, invite_to, bufferSplit, irc_server);
        }
	}
}
