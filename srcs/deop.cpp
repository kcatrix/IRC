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



static int isInChan(User executer, CHANNEL_ITERATOR &chan, STRING_VECTOR bufferSplit)
{
	for (USER_ITERATOR it = chan->chan_users.begin (); it != chan->chan_users.end (); it++)
	{
		if((*it).nickname == bufferSplit[2])
		{
			print_message (it->sd, "You now are deop from " + bufferSplit[1] + " by " + executer.nickname + "\n");
            STRING_ITERATOR ITR = std::find (chan->ope.begin(), chan->ope.end(), it->nickname);
            chan->ope.erase(ITR);
			return (1);
		}
	}
	return 0;
}

void    deop (User executer, STRING_VECTOR bufferSplit, Server& irc_server) {

    if(bufferSplit[1].empty () == 1 || bufferSplit[2].empty() == 1)
        print_message (executer.sd, "Not enough parameters given.\n");
    else {
        CHANNEL_ITERATOR chann_to_op = findChannel (bufferSplit[1], irc_server);
        if (chann_to_op == irc_server.channels.end ())
            print_message (executer.sd, "The chann : " + bufferSplit[1] + " you tried to deop to doesn't exist\n");
        else
        {
            if (isOpe(chann_to_op->ope, executer) == 1)
			{
				print_message (executer.sd, "You don't have enought right to deop in the channel :" + bufferSplit[1] + "\n");
			}
            else
			{
				if(isInChan(executer, chann_to_op, bufferSplit) == 0)
					print_message (executer.sd, "No user : " + bufferSplit[2] + " in channel : " + bufferSplit[1] +  "\n");
			}
        }
    }
}   