#include "../includes/irc.hpp"

void    ignore (User executer, User ignored_user) {
    executer.ignored.push_back (ignored_user);
    print_message (executer.sd, "The user " + ignored_user.nickname + " is now ignored.\n");
    print_message (ignored_user.sd, "You have been ignored by " + executer.nickname + ".\n");
}
