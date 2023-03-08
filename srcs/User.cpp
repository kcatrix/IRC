#include "../includes/irc.hpp"

User::User (void) : username (""), nickname (""), password (""), logInPwd (""), away_message (""), away (false), OP (false) , online (false), sd (0), x(0) { 
    ignored.reserve (1);
}

User::User (int sd) : username (""), nickname (""), password (""), logInPwd (""), away_message (""), away (false), OP (false) , online (false), sd (sd), x(0) { 
    ignored.reserve (1);
}

User::User (const User& cpy) : username (cpy.username), nickname (cpy.nickname), password (cpy.password), logInPwd (cpy.logInPwd), away_message (cpy.away_message), ignored (cpy.ignored), away (cpy.away), OP (cpy.OP), online (cpy.online), sd (cpy.sd), x(cpy.x) { }

User& User::operator=( User const & cp ) {
	username = cp.username;
	nickname = cp.nickname;
    password = cp.password;
    logInPwd = cp.logInPwd;
    away_message = cp.away_message;
    ignored = cp.ignored;
    away = cp.away;
    OP = cp.OP;
    online = cp.online;
	sd = cp.sd;
    x = cp.x;
	return *this;
}

User::~User(void) {
	username.clear ();
	nickname.clear ();
	password.clear ();
	logInPwd.clear ();
	away_message.clear ();
    ignored.clear ();
    away = false;
    OP = false;
    online = false;
	sd = 0;
    x = 0;
}

std::string User::getUsername(void) const { return username; }

USER_ITERATOR     User::findUser (CHANNEL_ITERATOR channel) {
    USER_ITERATOR   current_user = channel->chan_users.begin ();
    while (current_user != channel->chan_users.end ()) {
        if (current_user->nickname == nickname)
            return current_user;
        current_user++;
    }
    return current_user;
}

void    User::addUser (CHANNEL_ITERATOR channel) {
    USER_ITERATOR   user = findUser (channel);
    if (user == channel->chan_users.end ())
        print_message (sd, "You joined the channel #" + channel->channel_name + "\n");
    else
        print_message (sd, "You are already on the channel #" + channel->channel_name + "\n");
    
}

void    User::removeUser (CHANNEL_ITERATOR channel) {
    USER_ITERATOR   user = findUser (channel);
    if (user == channel->chan_users.end ())
        print_message (sd, channel->channel_name + ": You're not on that channel\n");
    else {
        channel->chan_users.erase (user);
        print_message (sd, "You left the channel #" + channel->channel_name + "\n");
    }
}
