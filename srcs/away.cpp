#include "../includes/irc.hpp"


void away(clien executer, char *buffer)
{
	char **buffspli = ft_split(buffer, ' ');
	if (buffspli[1] == NULL)
	{
		executer.away = false;
		std::string message = "You are no longer marked as being away\n";
		executer.away_message = ""; 
		free_tab(buffspli);
		return ;
	}
	executer.away = true;
	std::string message = "You are now marked as being away\n";
	write(executer.sd, message.c_str(), message.length() + 1);
	executer.away_message = buffspli[1];
	free_tab(buffspli);
}