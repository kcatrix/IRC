#include"head/irc.hpp"

irc::irc( void ){ return; }

irc::~irc( void ){ return; }

irc::irc( irc const & ){ return; }


irc & irc::operator=( irc const & cp )
{
	this->line = cp.line;
	this->all_commands = cp.all_commands;
	return *this;
}


void irc::init(int argc, char **argv)
{
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
			line.push_back(argv[i]);
		for (long unsigned int i = 0; i < line.size(); i++)
			std::cout << "Taille du vecteur : " << line[i] << std::endl;
	}
}