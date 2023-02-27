#include "../includes/clien.hpp"

clien::clien( void )
{ 
	this->sd = 0;
	return; 
}

clien::clien(int sd)
{ 
	this->sd = sd;
	std::cout << "Clien created sd = " << sd << std::endl;
	return; 
}

clien::clien(std::string str1, std::string str2, int sd)
{ 
	this->username = str1;
	this->nickname = str2;
	this->sd = sd;
	std::cout << "Clien created" << std::endl;
	return; 
}

clien::~clien( void )
{
	std::cout << "Clien destroyed" << std::endl; 
	return; 
}

clien & clien::operator=( clien const & cp )
{
	this->username = cp.username;
	this->nickname = cp.nickname;
	this->sd = cp.sd;
	return *this;
}

void clien::clear_clien(void)
{
	std::cout << "Clien cleared" << std::endl;
	this->username.clear();
	this->nickname.clear();
	this->sd = 0;
}

std::string clien::getUsername(void)
{
	return this->username;
}