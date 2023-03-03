#include "../includes/irc.hpp"

void modt(User executer)
{
	std::string message = "Welcome to the Internet Relay Network " + executer.nickname + "\n";
	write(executer.sd, message.c_str(), message.length() + 1);
}
