#include"../includes/irc.hpp"

int	main(int argc,char **argv)
{
    if (argc != 3 || std::atoi(argv[1]) == 0)
        print_error ("Wrong arguments. Use: ./ircserv <port> <password>.");
	
    start_irc (std::atoi(argv[1]), argv[2]);
	// parse(&irc)
}
