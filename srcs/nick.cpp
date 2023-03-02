#include "../includes/irc.hpp"

//  ----- a potentiellement modifier lors de la refonte du log de base du user -----------
void nick(User executer, char *buffer, std::vector<User> *users){ 

	char **buffspli = ft_split(buffer, ' ');
    if(buffspli[1] == NULL || (buffspli[1] != NULL && buffspli[2] != NULL))
        write(executer.sd, "Votre entree n'est pas valide ! (nick <Nickname>)\n", 51);
    else
    {
        if(checkdoublonnick(buffspli[1], *users, executer.sd) == 1)
            return ;
        executer.nickname = buffspli[1];
        write(executer.sd, "nick name :", 11);
        write (executer.sd, executer.nickname.c_str(), executer.nickname.length());
    }
    // write(newsocket, user_tab[i].nickname.c_str(), user_tab[i].nickname.length());
	free_tab(buffspli);
}

