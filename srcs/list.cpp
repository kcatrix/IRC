#include "../includes/irc.hpp"

void    list (User executer, CHANNEL_VECTOR& channels) {
    for (CHANNEL_ITERATOR it = channels.begin (); it != channels.end (); it++)
        print_message (executer.sd, it->channel_name + "\n");
}
