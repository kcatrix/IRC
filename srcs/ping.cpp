#include "../includes/irc.hpp"

void ping(User executer, std::vector<std::string> bufferSplit)
{
	if (bufferSplit[1].empty () == 1)
        print_error ("ERROR: No tokken\n");
    print_message (executer.sd, + "PONG" + bufferSplit[1] + "\n");
}
