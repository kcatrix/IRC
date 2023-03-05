#include "../includes/irc.hpp"

void    help (User executer, Server& irc_server) {
    for (std::vector<std::string>::iterator it = irc_server.commands_list.begin (); it != irc_server.commands_list.end (); it++)
        print_message (executer.sd, (*it) + "\n");
}
