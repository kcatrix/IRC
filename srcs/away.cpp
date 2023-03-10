#include "../includes/irc.hpp"

void    away (User& executer, STRING_VECTOR bufferSplit) {
	if (executer.away == true) {
		executer.away = false;
        print_message (executer.sd, "You are no longer marked as being away\n");
		executer.away_message.clear ();
	}
    else {
        std::string	reason;
        for (int y = 1; bufferSplit[y].empty () == 0; y++)
            reason = reason + " " + bufferSplit[y];
        executer.away = true;
        print_message (executer.sd, "You are now marked as being away\n");
        executer.away_message = reason;
    }
}
