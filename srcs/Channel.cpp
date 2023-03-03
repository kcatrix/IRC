#include "../includes/irc.hpp"

Channel::Channel (void) {
    chan_users.reserve (10);
}

Channel::Channel (std::string name) {
    chan_users.reserve (10);
    channel_name = name;
}

Channel::Channel (const Channel& cpy) : chan_users (cpy.chan_users) { }

Channel::~Channel (void) {
    chan_users.clear ();
}
