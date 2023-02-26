#include"../includes/irc.hpp"
#include"../includes/serv.hpp"
#include"../includes/utils.hpp"

int	main(int argc,char **argv)
{
    if (argc != 3 || std::atoi(argv[1]) == 0)
        print_error ("Wrong arguments. Use: ./ircserv <port> <password>.");
    Server  new_server (std::atoi(argv[1]), argv[2]);
	
	// parse(&irc)
}
