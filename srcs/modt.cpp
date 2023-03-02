#include "../includes/irc.hpp"

void modt(clien executer)
{
	std::string message = "Welcome to the Internet Relay Network " + executer.nickname + "\n";
	write(executer.sd, message.c_str(), message.length() + 1);
}