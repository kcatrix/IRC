#ifndef irc_HPP
# define irc_HPP
# include <iostream>
# include <cstring>
# include <vector>
# include <cstdlib>
# include <string>

class irc
{
	public :

	irc( void );
	irc( irc const & );
	irc & operator=( irc const & cp );
	~irc( void );
//--------------------Fonction-----------------------------------------------------------------------------------------

	int init(int argc, char** argv);
	int removeStringVector(std::vector<std::string>& myVector, const char* target);
	void printVector(std::vector<std::string>& myVector);
	void printVector(std::vector<int>& myVector);
	void copyVector(const std::vector<std::string> &src, std::vector<std::string> &dst);

//------------------------VARIABLE---------------------------------------------------------------------------------------

	std::vector<std::string> line;
	std::vector<std::string> all_commands;
	int port;
	std::string mdp;
};

#endif

