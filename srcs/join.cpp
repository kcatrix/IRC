#include "../includes/irc.hpp"

void    createChannel (std::string nickname, char* name, Server& irc_server) {
    std::string channel_name (name);
    std::cout << "sent name: " << name << std::endl;
    Channel     new_channel (channel_name);
    std::cout << "channel name entered: " << channel_name << ", new channel called: " << new_channel.channel_name << std::endl;

    std::cout << "number of channels: " << irc_server.channels.size () << std::endl;
    new_channel.chan_users.push_back (nickname);
    irc_server.channels.push_back (new_channel);
    std::cout << "number of channels: " << irc_server.channels.size () << std::endl;
    std::cout << "The channel " << irc_server.channels.front().channel_name << " was created." << std::endl;
    std::cout << "List of channels: " << std::endl;
    for (std::vector<Channel>::iterator it = irc_server.channels.begin (); it != irc_server.channels.end (); it++) {
        std::cout << "current channel name: " << (*it).channel_name << ", looking for: " << channel_name << std::endl;
    }
}

void    join (User executer, char* buffer, Server& irc_server) {
	char **buffspli = ft_split(buffer, ' ');
    if(buffspli[1] == NULL || (buffspli[1] != NULL && buffspli[2] != NULL)) {
        print_message (executer.sd, "Votre entree n'est pas valide ! (join <channel name>)\n");
        return;
    }
    std::string channel_name (buffspli[1]);
    for (std::vector<Channel>::iterator it = irc_server.channels.begin (); it != irc_server.channels.end (); it++) {
        if ((*it).channel_name == channel_name) {
            print_message (executer.sd, "You joined the channel" + channel_name);
            return;
        }
    }
    createChannel (channel_name, buffspli[1], irc_server);
}
