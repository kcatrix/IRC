#ifndef irc_HPP
# define irc_HPP
# include <iostream>
# include <vector>

class irc
{
	public :

	irc( void );
	irc( irc const & );
	irc & operator=( irc const & cp );
	~irc( void );

	void init(int argc, char** argv);
	void removeString(std::vector<std::string>& myVector, const char* target);
	void printVector(std::vector<std::string>& myVector);

	std::vector<std::string> line;
	std::vector<std::string> all_commands;
};

#endif
