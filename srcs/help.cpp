#include "../includes/irc.hpp"

void    printCommandsList (int sd, STRING_VECTOR commands_list) {
    for (STRING_ITERATOR it = commands_list.begin (); it != commands_list.end (); it++)
        print_message (sd, (*it).erase (0, 1) + "\n");
}

void    printHelp (std::string command) {
}

void    help (User executer, std::string command, Server& irc_server) {
    if (command.empty ())
        printCommandsList (executer.sd, irc_server.commands_list);
    else if (checkCommand (executer.sd, command, irc_server) == 1)
        printHelp (command);
    return;
}
