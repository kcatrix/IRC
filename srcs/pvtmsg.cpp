#include "../includes/irc.hpp"

static int isIgnored (USER_ITERATOR tocheck, User executer) {
    for (USER_ITERATOR it = tocheck->ignored.begin (); it != tocheck->ignored.end (); it++) {
        if(it->nickname == executer.nickname)
            return 1;
    }
    return 0;
}

static int isInChan (User executer, CHANNEL_ITERATOR chan) {
	for (USER_ITERATOR it = chan->chan_users.begin (); it != chan->chan_users.end (); it++) {
		if(executer.nickname == it->nickname)
			return 1;
	}
	return 0;
}

void msg (User& executer, STRING_VECTOR bufferSplit, USER_VECTOR users, Server& irc_server) {
	std::string	message;
    if (bufferSplit[1].empty() == 1 || bufferSplit[2].empty() == 1) {
        print_message (executer.sd, "Not enough parameters given.\n");
        return ;
    }
    if (bufferSplit[1][0] != '#') {
        for (USER_ITERATOR it = users.begin (); it != users.end (); it++) {
            if (bufferSplit[1] == (*it).nickname) {
                if (isIgnored (it, executer) == 0) {
                    if (it->away == true ) {
                        message = it->nickname + " is away:" + it->away_message + '\n'; 
                        print_message (executer.sd, message);
                        return ;
                    }
                    if (bufferSplit[2].empty () == 0)
                        message = bufferSplit[2];
                    for (int y = 3; bufferSplit[y].empty () == 0; y++)
                        message = message + " " + bufferSplit[y];
                    print_message (it->sd, "<" + executer.nickname + ">" + message + "\n");
                }
            }
        }
    }
    else {
        CHANNEL_ITERATOR to_send = findChannel (bufferSplit[1], irc_server);
        if (to_send == irc_server.channels.end ()) {
            print_message (executer.sd, "This channel doesn't exist\n");
            return;
        }
        if (isInChan (executer, to_send) == 0)
            print_message (executer.sd, "You cannot send message in a channel you're not in\n");
        else {
            for (USER_ITERATOR it = to_send->chan_users.begin (); it != to_send->chan_users.end (); it++) {
                USER_ITERATOR itr = users.begin ();
                while (itr != users.end ()) {
                    if (itr->nickname == it->nickname)
                        break;
                    itr++;
                }
                if (isIgnored (itr, executer) == 0) {
                    if (it->away == true ) {
                        message = it->away_message + '\n';
                        print_message (it->sd, message);
                    }
                    else {
                        if (bufferSplit[2].empty () == 0)
                            message = bufferSplit[2];
                        for (int y = 3; bufferSplit[y].empty () == 0; y++)
                            message = message + " " + bufferSplit[y];
                        print_message ((*it).sd, "<" + executer.nickname + ">" + message + "\n");
                    }
                }
            }
        }
    }
}
