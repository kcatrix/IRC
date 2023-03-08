#include "../includes/irc.hpp"

static User getUser(Server& irc_server, std::string to_ignore)
{
    for (USER_ITERATOR it = irc_server.users.begin (); it != irc_server.users.end (); it++)
	{
        if((*it).nickname == to_ignore)
            return (*it);
    }
    return User();
}

void    accept (User &executer, std::string to_accept, Server& irc_server) {

    User ignored_user = getUser(irc_server, to_accept);
    if(ignored_user.nickname == "")
        print_message (executer.sd, "The user " + to_accept + " doesn't exist.\n");
    USER_ITERATOR   ignored = std::find (executer.ignored.begin (), executer.ignored.end (), ignored_user);
    if(ignored == executer.ignored.end())
    {
        print_message (executer.sd, "The user " + ignored_user.nickname + " isn't in your ignore list.\n");
        return;
    }
    executer.ignored.erase (ignored);
    print_message (executer.sd, "The user " + ignored_user.nickname + " ignored status has been removed.\n");
    print_message (ignored_user.sd, "You are not ignored by " + executer.nickname + ".\n");
}
