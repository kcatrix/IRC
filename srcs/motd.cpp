#include "../includes/irc.hpp"

void motd (User executer) {
    print_message (executer.sd, "Welcome to the Internet Relay Network, " + executer.nickname + ".\n");
}
