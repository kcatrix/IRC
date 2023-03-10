#include "../includes/irc.hpp"

Channel::Channel (void) : channel_name (""){
    chan_users.reserve (1);
    ope.reserve (1);
    banned.reserve (1);
}


Channel::Channel (std::string name) : channel_name (name) {
    chan_users.reserve (1);
    ope.reserve (1);
    banned.reserve (1);
}

Channel::Channel (const Channel& cpy) : channel_name (cpy.channel_name), chan_users (cpy.chan_users), ope(cpy.ope) , banned(cpy.banned){ }

Channel::~Channel (void) {
    channel_name.clear ();
    chan_users.clear ();
    ope.clear ();
    banned.clear ();
}
