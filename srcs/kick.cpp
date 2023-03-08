#include "../includes/irc.hpp"

static int	isOpe(STRING_VECTOR ope, User executer)
{
	for (STRING_ITERATOR it = ope.begin (); it != ope.end (); it++)
	{
		if((*it) == executer.nickname)
			return(0);
	}
	return (1);
}

static int isInChan(User executer, USER_VECTOR &chan_user, STRING_VECTOR bufferSplit)
{
	for (USER_ITERATOR it = chan_user.begin (); it != chan_user.end (); it++)
	{
		if((*it).nickname == bufferSplit[2])
		{
			std::string message = bufferSplit[3];
            for(int y = 4; bufferSplit[y].empty () == 0; y++)
                message = message + " " + bufferSplit[y];
			print_message ((*it).sd, "Kicked from channel " + bufferSplit[1] + " by " + executer.nickname + " : " + message + "\n");
			chan_user.erase(it);
			return (1);
		}
	}
	return 0;
}

void    kick (User executer, STRING_VECTOR bufferSplit, Server& irc_server) {

    if(bufferSplit[1].empty () == 1 || bufferSplit[2].empty () == 1 || bufferSplit[3].empty () == 1)
        print_message (executer.sd, "Not enough parameters given.\n");
    else {
        CHANNEL_ITERATOR kick_from = findChannel (bufferSplit[1], irc_server);
        if (kick_from == irc_server.channels.end ())
            print_message (executer.sd, "The chann : " + bufferSplit[1] + " you tried to kick from doesn't exist\n");
        else
        {
			if (isOpe(kick_from->ope, executer) == 1)
			{
				print_message (executer.sd, "You don't have enought right to kick from the channel :" + bufferSplit[1] + "\n");
			}
			else
			{
				if(isInChan(executer, kick_from->chan_users, bufferSplit) == 0)
					print_message (executer.sd, "No user : " + bufferSplit[2] + " in channel : " + bufferSplit[1] +  "\n");
			}
			//find user in chann
        }
	}
}