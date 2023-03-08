#include "../includes/irc.hpp"


void away(User executer, std::vector<std::string> bufferSplit) {
	if (bufferSplit[1].empty ()) {
		executer.away = false;
		std::string message = "You are no longer marked as being away\n";
		executer.away_message = ""; 
		return ;
	}
	executer.away = true;
	std::string message = "You are now marked as being away\n";
    print_message (executer.sd, message);
	write(executer.sd, message.c_str(), message.length() + 1);
	executer.away_message = bufferSplit[1];
}
