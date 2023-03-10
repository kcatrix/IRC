#include "../includes/irc.hpp"

static int isIgnored (const std::string nickname, USER_VECTOR ignored) {
    for (USER_ITERATOR it = ignored.begin (); it != ignored.end (); it++) {
        if (nickname == it->nickname)
            return 1;
    }
    return 0;
}

void    accept (User& executer, std::string to_accept, Server& irc_server) {
    User    ignored_user = getUser (irc_server.users, to_accept);

    if (ignored_user.nickname == "")
        print_message (executer.sd, "The user " + to_accept + " doesn't exist.\n");
    else if (isIgnored (ignored_user.nickname, executer.ignored) == 0 and executer != ignored_user)
        print_message (executer.sd, "The user " + ignored_user.nickname + " isn't in your ignore list.\n");
    else if (executer != ignored_user) {
        USER_ITERATOR   ignored = std::find (executer.ignored.begin (), executer.ignored.end (), ignored_user);
        executer.ignored.erase (ignored);
        print_message (executer.sd, "The user " + ignored_user.nickname + " ignored status has been removed.\n");
        print_message (ignored_user.sd, "You are no longer ignored by " + executer.nickname + ".\n");
    }
}

void    ignore (User &executer, std::string to_ignore, Server& irc_server) {
    User    ignored_user = getUser (irc_server.users, to_ignore);

    if (ignored_user.nickname == "")
        print_message (executer.sd, "The user " + to_ignore + " doesn't exist.\n");
    else if (isIgnored (ignored_user.nickname, executer.ignored) == 1)
        print_message (executer.sd, "The user " + to_ignore + " is already in your ignore list.\n");
    else if (executer != ignored_user) {
        executer.ignored.push_back (ignored_user);
        print_message (executer.sd, "The user " + ignored_user.nickname + " is now ignored.\n");
        print_message (ignored_user.sd, "You have been ignored by " + executer.nickname + ".\n");
    }
}
