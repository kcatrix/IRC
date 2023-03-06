#include "../includes/irc.hpp"

void deop(User executer, STRING_VECTOR bufferSplit, std::vector<User> users)
{
	if (executer.OP == false)
	{
		print_message(executer.sd, "You are not an OP\n");
		return ;
	}
	else
	{
		for (USER_ITERATOR it = users.begin (); it != users.end (); it++)
		{
			if ((*it).nickname == bufferSplit[1])
			{
				(*it).OP = false;
				print_message((*it).sd, "You are now an OP\n");
				return ;
			}
		}
	}
}