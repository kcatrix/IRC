#pragma once

# include "irc.hpp"

class User {

	public:

		User (void);
		User (const int sd);
		User (const User& cpy);
		User & operator=(User const & cp);
		virtual ~User (void);

		std::string getUsername (void) const;
        void        addUser (CHANNEL_ITERATOR channel);
        User		getUser (USER_VECTOR users, std::string nickname);
        void        removeUser (CHANNEL_ITERATOR channel);
        USER_ITERATOR   findUser (CHANNEL_ITERATOR channel);

		std::string username;
		std::string nickname;
		std::string logInPwd;
		std::string away_message;
		USER_VECTOR ignored;
		bool        away;
		bool        OP;
		bool        online;
		int         sd;
        int         info;

        bool    operator== (const User& rhs) const { return this->nickname == rhs.nickname; }
        bool    operator!= (const User& rhs) { return !(*this == rhs); }
};

