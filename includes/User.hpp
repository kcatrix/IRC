#pragma once

# include <string>

class User
{
	public:
		User();
		User(int sd);
		User(std::string str1, std::string str2, int sd);
		User & operator=( User const & cp);
		std::string getUsername(void);
		void clear_user(void);
		~User();

		std::string username;
		std::string nickname;
		std::string password;
		bool        OP;
		int         sd;
};
