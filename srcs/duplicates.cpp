#include "../includes/irc.hpp"

int checkDuplicateNick (std::string to_check, USER_VECTOR users) {
    if (getUser (users, to_check).nickname == "")
        return 0;
    return 1;
}

int checkDuplicateUser (std::string to_check, USER_VECTOR users, int sd) {
    for (USER_ITERATOR it = users.begin (); it != users.end (); it++) {
		if(it->nickname.compare (to_check) == 0) {
			if (sd == it->sd)
				print_message (sd, "This is already your username\n"); 
			else
				print_message (sd, "Username already in use.n"); 
			return 1;
		}
	}
	return 0;
}
