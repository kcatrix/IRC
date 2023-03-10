#include "../includes/irc.hpp"

void   userhost (User executer, STRING_VECTOR bufferSplit, Server& irc_server) {
    if (bufferSplit[1].empty () == 1)
        print_message (executer.sd, "Not enough parameters given.\n");
    for (USER_ITERATOR it = irc_server.users.begin (); it != irc_server.users.end (); it++) {
        if (it->nickname == bufferSplit[1]) {
            std::string message = it->nickname + "=+~" + it->username + "@127.0.0.1";
            print_message (executer.sd, message + "\n");
            return;
        }
    }
}
