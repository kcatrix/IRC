#include "../includes/irc.hpp"

int checkDuplicateNick (std::string to_check, USER_VECTOR users) {
    if (getUser (users, to_check).nickname == "")
        return 0;
    return 1;
}

int checkDuplicateUser (std::string to_check, USER_VECTOR users, int sd) {
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
