#include "../includes/irc.hpp"

void ping(User executer, char *buffer)
{
	int newsocket = executer.sd;
	char **buffspli = ft_split(buffer, ' ');
	if (buffspli[1] == NULL)
	{
		write(newsocket, "ERROR :No tokken\n", 17);
		return ;
	}
	std::string tokken = buffspli[1];
	std::string message = "PONG " + tokken + "\n";
	write(newsocket, message.c_str(), message.length() + 1);
	free_tab(buffspli);
}
