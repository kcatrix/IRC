#include "../includes/irc.hpp"

User::User (void) : username (""), nickname (""), logInPwd (""), away_message (""), away (false), OP (false) , online (false), sd (0), info(0) { 
    ignored.reserve (1);
}

User::User (int sd) : username (""), nickname (""), logInPwd (""), away_message (""), away (false), OP (false) , online (false), sd (sd), info(0) { 
    ignored.reserve (1);
}

User::User (const User& cpy) : username (cpy.username), nickname (cpy.nickname), logInPwd (cpy.logInPwd), away_message (cpy.away_message), ignored (cpy.ignored), away (cpy.away), OP (cpy.OP), online (cpy.online), sd (cpy.sd), info(cpy.info) { }

User& User::operator= (User const& cp) {
	username = cp.username;
	nickname = cp.nickname;
    logInPwd = cp.logInPwd;
    away_message = cp.away_message;
    ignored = cp.ignored;
    away = cp.away;
    OP = cp.OP;
    online = cp.online;
    info = cp.info;
	return *this;
}

User::~User(void) {
	username.clear ();
	nickname.clear ();
	logInPwd.clear ();
	away_message.clear ();
    ignored.clear ();
    away = false;
    OP = false;
	sd = 0;
    info = 0;
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
