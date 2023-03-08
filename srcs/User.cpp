#include "../includes/irc.hpp"

User::User (void) : username (""), nickname (""), password (""), logInPwd (""), away_message (""), away (false), OP (false) ,
                    online (false), sd (0), x(0) { 
                        ignored.reserve (MAX_USERS);
}

User::User(int sd)
{ 
    x = 0;
    this->away = 0;
	this->sd = sd;
	return; 
}

User::~User( void )
{
	//std::cout << "User destroyed" << std::endl; 
	return; 
}

User & User::operator=( User const & cp )
{
	this->username = cp.username;
	this->nickname = cp.nickname;
    password = cp.password;
    logInPwd = cp.logInPwd;
    away_message = cp.away_message;
    ignored = cp.ignored;
    away = cp.away;
    OP = cp.OP;
    online = cp.online;
	this->sd = cp.sd;
    this->x = cp.x;
	return *this;
}

void User::clear_user(void)
{
	std::cout << "User cleared" << std::endl;
	this->username.clear();
	this->nickname.clear();
	this->sd = 0;
}

std::string User::getUsername(void)
{
	return this->username;
}

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
    if (user == channel->chan_users.end ()) {
        //channel->chan_users.push_back ((*user));
        print_message (sd, "You joined the channel #" + channel->channel_name + "\n");
    }
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
