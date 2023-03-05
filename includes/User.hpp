#pragma once

# include "irc.hpp"

class User
{
	public:
		User();
		User(int sd);
		User(std::string str1, std::string str2, int sd);
		User & operator=( User const & cp);
		~User();

		std::string getUsername(void);
		void        clear_user(void);
        USER_ITERATOR         findUser (CHANNEL_ITERATOR channel);
        void        addUser (CHANNEL_ITERATOR it);
        void        removeUser (CHANNEL_ITERATOR it);



		std::string username;
		std::string nickname;
		std::string password;
		std::string away_message;
		bool        away;
		bool        OP;
		int         sd;
};
