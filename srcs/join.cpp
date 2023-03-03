#include "../includes/irc.hpp"

void    createChannel (User executer, std::string channel_name, Server& irc_server) {
    Channel     new_channel (channel_name);

    new_channel.chan_users.push_back (executer.nickname);
    irc_server.channels.push_back (new_channel);
    std::cout << "The channel " << irc_server.channels.back ().channel_name << " was created by " << irc_server.channels.back ().chan_users.back () << std::endl;
    print_message (executer.sd, "You created the channel #" + irc_server.channels.back ().channel_name + "\n");
}

int     findChannel (std::string channel_name, Server& irc_server) {
    for (std::vector<Channel>::iterator it = irc_server.channels.begin (); it != irc_server.channels.end (); it++) {
        if ((*it).channel_name == channel_name)
            return 1;
    }
    return 0;
}

void    addUser (User executer, std::string channel_name, Server& irc_server) {
    for (std::vector<Channel>::iterator it = irc_server.channels.begin (); it != irc_server.channels.end (); it++) {
        if ((*it).channel_name == channel_name) {
            (*it).chan_users.push_back (executer.nickname);
            print_message (executer.sd, "You joined the channel #" + (*it).channel_name + "\n");
        }
    }
}

void    join (User executer, char* buffer, Server& irc_server) {
	char **buffspli = ft_split(buffer, ' ');
    if(buffspli[1] == NULL || (buffspli[1] != NULL && buffspli[2] != NULL)) {
        print_message (executer.sd, "Votre entree n'est pas valide ! (join <channel name>)\n");
        return;
    }
    std::string channel_name (buffspli[1]);
    if (findChannel (channel_name, irc_server) == 0)
        createChannel (executer, channel_name, irc_server);
    else {
        addUser (executer, channel_name, irc_server);
        //(*it).chan_users.push_back (executer.nickname);
        print_message (executer.sd, "You joined the channel #" + channel_name + "\n");
        return;
    }
    std::cout << "List of channels: " << std::endl;
    for (std::vector<Channel>::iterator it = irc_server.channels.begin (); it != irc_server.channels.end (); it++)
        std::cout << (*it).channel_name << std::endl;
    std::cout << "end of list" << std::endl;
}
