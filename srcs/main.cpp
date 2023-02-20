#include"../includes/irc.hpp"
#include"../includes/serv.hpp"

int	main(int argc,char **argv)
{
	irc irc;
	
	
	if (irc.init(argc,argv) == 2)
		server(&irc);
	// parse(&irc)
}