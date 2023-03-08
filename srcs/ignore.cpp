#include "../includes/irc.hpp"


static int isIgnored(std::string nickname, USER_VECTOR ignored)
{
    for (USER_ITERATOR it = ignored.begin (); it != ignored.end (); it++)
	{
        if(nickname == (*it).nickname)
            return 1;
    }
    return 0;
}

static User getUser(Server& irc_server, std::string to_ignore)
{
    for (USER_ITERATOR it = irc_server.users.begin (); it != irc_server.users.end (); it++)
	{
        if((*it).nickname == to_ignore)
            return (*it);
    }
    return User();
}

void    ignore (User &executer, std::string to_ignore, Server& irc_server) {

    User ignored_user = getUser(irc_server, to_ignore);
    if(ignored_user.nickname == "")
    {
        print_message (executer.sd, "The user " + to_ignore + " doesn't exist.\n");
        return;
    }
    else if (isIgnored(ignored_user.nickname, executer.ignored) == 1)
    {
        print_message (executer.sd, "The user " + to_ignore + " is already in your ignore list.\n");
        return;
    }
    executer.ignored.push_back (ignored_user);
    print_message (executer.sd, "The user " + ignored_user.nickname + " is now ignored.\n");
    print_message (ignored_user.sd, "You have been ignored by " + executer.nickname + ".\n");
}
