#include "../includes/irc.hpp"

// ------------------------    Gestion doublons Nick / User --------------------------------------

int checkdoublonnick(char *tocheck, std::vector<clien> clients, int sd) //doublon nick
{
    for (ITERATOR it = clients.begin (); it != clients.end (); it++)
    {
		if((*it).nickname.compare(tocheck) == 0)
		{
			if(sd == (*it).sd)
				write(sd, "This is already your nickname !\n", 32);
			else
				write(sd, "nickname already in use, please try an other one\n", 49);
			return 1;
		}
	}
	return 0;
}

int checkdoublonuser(char *tocheck, std::vector<clien> clients, int sd) //doublon user
{
    for (ITERATOR it = clients.begin (); it != clients.end (); it++)
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
