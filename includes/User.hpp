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
        void    addUser (CHANNEL_ITERATOR channel);
        void    removeUser (CHANNEL_ITERATOR channel);
		void        clear_user(void);
        USER_ITERATOR         findUser (CHANNEL_ITERATOR channel);

		std::string username;
		std::string nickname;
		std::string password;
		std::string away_message;
		USER_VECTOR ignored;
		bool        away;
		bool        OP;
		int         sd;

    private:

		User (void);
};

template <class U1, class U2>
bool    operator== (const U1& lhs, const U2 rhs) { return lhs.nickname == rhs.nickname; }
