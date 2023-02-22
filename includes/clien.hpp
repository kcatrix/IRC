#ifndef CLIEN_HPP
# define CLIEN_HPP

#include <iostream>
#include <string>

class clien
{
	public:
		clien();
		clien(std::string str1, std::string str2);
		clien & operator=( clien const & cp);
		std::string getUsername(void);
		~clien();

		std::string username;
		std::string nickname;
};

#endif