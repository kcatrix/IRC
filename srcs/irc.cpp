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
		line.erase(line.begin() + 1);
		for (long unsigned int i = 0; i < line.size(); i++)
			std::cout << "Taille du vecteur : " << line.size() << "   val :" <<  line[i] << std::endl;
	}
}

#include <vector>
#include <string>
/* 

exemple manipulation vector

int main() {
  std::vector<std::string> myVector = {"Hello", "World", "Goodbye"};
  std::string target = "World";
  
  for (int i = 0; i < myVector.size(); ++i) {
    if (myVector[i] == target) {
      myVector.erase(myVector.begin() + i);
      break;
    }
  }
  
  return 0;
}

*/
