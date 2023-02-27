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


int irc::init(int argc, char **argv)
{
	if (argc == 3)
	{
		for (int i = 1; i < argc; i++)
			line.push_back(argv[i]);
		port = atoi(line[0].c_str());
		mdp = line[1];
		printVector(line);
		return (0);
	}
	else if (argc == 1)
		return (2);
	return (1);
}

int irc::removeStringVector(std::vector<std::string>& myVector, const char* target)
{
	int lenght = myVector.size();
	for (int i = 0; i < lenght; ++i) 
	{
    	if (myVector[i] == target) 
		{
      		myVector.erase(myVector.begin() + i);
			return (0);
      		break;
		}
	}
	std::cout << "not find \n"; 
	return(1);
}

void irc::copyVector(const std::vector<std::string> &src, std::vector<std::string> &dst)
{
    for (long unsigned int i = 0; i < src.size(); i++)
    {
        dst.push_back(src[i]);
    }
}

void irc::printVector(std::vector<std::string>& myVector)
{
	std::cout << "Taille du vecteur : " << myVector.size() << "\n";
	for (long unsigned int i = 0; i < myVector.size(); i++)
			std::cout << "   value "  << i << " == " <<  myVector[i] << std::endl;
}

void irc::printVector(std::vector<int>& myVector)
{
	std::cout << "Taille du vecteur : " << myVector.size() << "\n";
	for (long unsigned int i = 0; i < myVector.size(); i++)
			std::cout << "   value "  << i << " == " <<  myVector[i] << std::endl;
}


