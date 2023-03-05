#pragma once

# include "irc.hpp"

class User
{
	public:
		User (int sd);
		User (const User& cpy) : username (cpy.username), nickname (cpy.nickname), password (cpy.password),
        away_message (cpy.away_message), away (cpy.away), OP (cpy.OP), sd (cpy.sd) { }
		User & operator=(User const & cp);
		virtual ~User (void);

		std::string getUsername(void);
		void        clear_user(void);
        USER_ITERATOR         findUser (CHANNEL_ITERATOR channel);

		std::string username;
		std::string nickname;
		std::string password;
		std::string away_message;
		bool        away;
		bool        OP;
		int         sd;

    private:

		User (void) { }
};
