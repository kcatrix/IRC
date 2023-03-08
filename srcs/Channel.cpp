#include "../includes/irc.hpp"

Channel::Channel (void) : channel_name (std::string ()) { }

Channel::Channel (std::string name) : channel_name (name) { }

Channel::Channel (const Channel& cpy) : channel_name (cpy.channel_name), chan_users (cpy.chan_users), ope(cpy.ope) , banned(cpy.banned){ }

Channel::~Channel (void) {
    chan_users.clear ();
}
