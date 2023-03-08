#include "../includes/irc.hpp"

void    accept (User executer, User ignored_user) {
    USER_ITERATOR   ignored = std::find (executer.ignored.begin (), executer.ignored.end (), ignored_user);
    executer.ignored.erase (ignored);
    print_message (executer.sd, "The user " + ignored_user.nickname + " ignored status has been removed.\n");
    print_message (ignored_user.sd, "You are not ignored by " + executer.nickname + ".\n");
}
