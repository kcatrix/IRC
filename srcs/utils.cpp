#include "../includes/irc.hpp"

void    print_error (std::string error_message) {
    std::cout << error_message << std::endl;
    exit (EXIT_FAILURE);
}

bool    CheckClientExists (std::vector<clien> clients, int fd) {
    for (std::vector<clien>::iterator it = clients.begin (); it != clients.end (); it++) {
        if ((*it).sd == fd)
            return 1;
    }
    return 0;
}

void    removeInvisibleChars(char* str)
{
    int i = 0;
    while (str[i])
        i++;
    i--;
    str[i] = '\0';
}

int     removeStringVector(std::vector<std::string>& myVector, const char* target)
{
    int length = myVector.size();
    for (int i = 0; i < length; ++i) 
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
