#include "../includes/irc.hpp"

void    nick (User& executer, STRING_VECTOR bufferSplit, USER_VECTOR users) {
    if (bufferSplit[1].empty ()) {
        print_message (executer.sd, "Your nickname is " + executer.nickname);
        return;
    }
    else {
        if (isalpha (bufferSplit[1][0]) == 0) {
            print_message (executer.sd, "Your nickname must start with a letter.\n");
            return;
        }
        if (checkDuplicateNick (bufferSplit[1], users) == 1) {
            if (bufferSplit[1] != executer.nickname)
                print_message (executer.sd, "Username already in use.\n");
            return;
        }
        executer.nickname = bufferSplit[1];
        print_message (executer.sd, "You're now known as " + executer.nickname + "\n");
    }
}
