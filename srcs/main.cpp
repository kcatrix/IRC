#include"../includes/irc.hpp"
#include"../includes/serv.hpp"

int	main(int argc,char **argv)
{
	irc irc;
	
	irc.init(argc,argv);
	// parse(&irc)
	run(&irc);
}