#include "../includes/irc.hpp"

void    createChannel (User executer, std::string channel_name, Server& irc_server) {
    Channel     new_channel (channel_name);

    new_channel.chan_users.push_back (executer.nickname);
    irc_server.channels.push_back (new_channel);
    std::cout << "The channel " << irc_server.channels.back ().channel_name << " was created by " << irc_server.channels.back ().chan_users.back () << std::endl;
    print_message (executer.sd, "You created the channel #" + irc_server.channels.back ().channel_name + "\n");
}

Channel     findChannel (std::string channel_name, Server& irc_server) {
    for (std::vector<Channel>::iterator it = irc_server.channels.begin (); it != irc_server.channels.end (); it++) {
        if ((*it).channel_name == channel_name)
            return *it;
    }
    return Channel ();
}

int     findUser (Channel to_join, std::string nickname) {
    for (std::vector<std::string>::iterator it = to_join.chan_users.begin (); it != to_join.chan_users.end (); it++) {
        if ((*it) == nickname)
            return 1;
    }
    return 0;
}

void    addUser (User executer, Channel to_join, Server& irc_server) {
    for (std::vector<Channel>::iterator it = irc_server.channels.begin (); it != irc_server.channels.end (); it++) {
        if ((*it).channel_name == to_join.channel_name) {
            if (findUser (to_join, executer.nickname) == 0) {
                (*it).chan_users.push_back (executer.nickname);
                print_message (executer.sd, "You joined the channel #" + (*it).channel_name + "\n");
            }
            else
                print_message (executer.sd, "You are already in the channel #" + (*it).channel_name + "\n");
        }
    }
}

void    join (User executer, std::vector<std::string> bufferSplit, Server& irc_server) {
    if(bufferSplit[1].empty () == 1 or (bufferSplit[1].empty () == 0 and bufferSplit[2].empty () == 0)) {
        print_message (executer.sd, "Votre entree n'est pas valide ! (join <channel name>)\n");
        return;
    }
    Channel to_join = findChannel (bufferSplit[1], irc_server);
    if (to_join.channel_name.empty () == 1)
        createChannel (executer, bufferSplit[1], irc_server);
    else
        addUser (executer, to_join, irc_server);
}
