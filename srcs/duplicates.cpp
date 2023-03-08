#include "../includes/irc.hpp"

// ------------------------    Gestion doublons Nick / User --------------------------------------

int checkDuplicateNick(std::string to_check, std::vector<User> users, int sd) //doublon nick
{
    for (USER_ITERATOR it = users.begin (); it != users.end (); it++) {
		if((*it).nickname == to_check)
			return 1;
	}
	return 0;
}

int checkdoublonuser(char *tocheck, std::vector<User> users, int sd) //doublon user
{
    for (USER_ITERATOR it = users.begin (); it != users.end (); it++)
    {
		if((*it).nickname.compare(tocheck) == 0)
		{
			if(sd == (*it).sd)
				write(sd, "This is already your username !\n", 32);
			else
				write(sd, "username already in use, please try an other one\n", 49);
			return 1;
		}
	}
	return 0;
}
