#include "../includes/irc.hpp"

void quit (User& executer) {
    print_message (executer.sd, "Goodbye " + executer.nickname + " !\n");
    close (executer.sd);
    executer.sd = 0;
}
