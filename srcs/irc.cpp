#include"../includes/irc.hpp"

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
		
		// removeString(line, "dudu");
		printVector(line);
		
	}
}

void irc::removeString(std::vector<std::string>& myVector, const char* target)
{
	int lenght = myVector.size();
	for (int i = 0; i < lenght; ++i) 
	{
    	if (myVector[i] == target) 
		{
      	myVector.erase(myVector.begin() + i);
      	break;
		}
	}
}

void irc::printVector(std::vector<std::string>& myVector)
{
	std::cout << "Taille du vecteur : " << myVector.size() << "\n";
	for (long unsigned int i = 0; i < myVector.size(); i++)
			std::cout << "   value :"  << i <<  myVector[i] << std::endl;
}
