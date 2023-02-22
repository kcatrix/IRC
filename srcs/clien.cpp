#include "../includes/clien.hpp"

clien::clien( void )
{ 
	std::cout << "Clien created void" << std::endl;
	return; 
}

clien::clien(std::string str1, std::string str2)
{ 
	this->username = str1;
	this->nickname = str2;
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
	return *this;
}

std::string clien::getUsername(void)
{
	return this->username;
}