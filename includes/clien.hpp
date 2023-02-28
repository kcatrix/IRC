#ifndef CLIEN_HPP
# define CLIEN_HPP

#include <iostream>
#include <string>

class clien
{
	public:
		clien();
		clien(int sd);
		clien(std::string str1, std::string str2, int sd);
		clien & operator=( clien const & cp);
		std::string getUsername(void);
		void clear_clien(void);
		~clien();

		std::string username;
		std::string nickname;
		std::string password;
		std::string hostname;
		std::string hostmask;
		int sd;
};



#endif