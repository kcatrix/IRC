#include "../includes/irc.hpp"

User::User( void )
{ 
	this->sd = 0;
	this->OP = false;
	this->away = false;
	return; 
}

User::User(int sd)
{ 
	this->sd = sd;
	std::cout << "User created sd = " << sd << std::endl;
	return; 
}

User::User(std::string str1, std::string str2, int sd)
{ 
	this->username = str1;
	this->nickname = str2;
	this->sd = sd;
	std::cout << "User created" << std::endl;
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
	this->sd = cp.sd;
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

int     User::findUser (CHANNEL_ITERATOR channel) {
    for (STRING_ITERATOR current_user = channel->chan_users.begin (); current_user != channel->chan_users.end (); current_user++) {
        if (*current_user == nickname)
            return 1;
    }
    return 0;
}

void    User::addUser (CHANNEL_ITERATOR it) {
    if (findUser (it) == 0) {
        (*it).chan_users.push_back (nickname);
        print_message (sd, "You joined the channel #" + (*it).channel_name + "\n");
    }
    else
        print_message (sd, "You are already in the channel #" + (*it).channel_name + "\n");
}
