#pragma once

#include <vector>

class Channel {

    public:

        Channel (void);
        Channel (std::string channel_name);
        Channel (const Channel& cpy);
        virtual ~Channel (void);

        std::string                 channel_name; 
        std::vector<std::string>    chan_users;
};
