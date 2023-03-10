#pragma once

# include "irc.hpp"

class Channel {

    public:

        Channel (void);
        Channel (std::string channel_name);
        Channel (const Channel& cpy);
        virtual ~Channel (void);

        std::string		channel_name;
        USER_VECTOR		chan_users;
		STRING_VECTOR	ope;
		STRING_VECTOR	banned;
};
