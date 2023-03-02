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
