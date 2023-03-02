/*int checkInfoClient(int new_socket, char *buffer, std::vector<clien> client_tab, std::string password)
{
    removeInvisibleChars(buffer);
    std::string message;
    std::string commande;

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (client_tab[i].sd == new_socket)
        {
            if (client_tab[i].password == "")
            {
                if (password.compare(buffer) == 0)
                {
                    client_tab[i].password = buffer;
                    write(new_socket, "Enter your username: ", 21);
                    return (1);
                }
                else
                {
                    write(new_socket, "Wrong password, try again: ", 27);
                    return (1);
                }
            }
            else if (client_tab[i].username == "")
            {
                client_tab[i].username = buffer;
                write(new_socket, "Enter your nickname: ", 21);
                return(1);
            }
            else if (client_tab[i].nickname == "")
            {
                // Remove any newline or carriage return characters from the end of the buffer
                int len = strlen(buffer);
                while (len > 0 && (buffer[len-1] == '\n' || buffer[len-1] == '\r')) {
                    buffer[--len] = '\0';
                }
                
                client_tab[i].nickname = buffer;
                message = "Welcome " + client_tab[i].username + " " + client_tab[i].nickname + " !\n";
                write(new_socket, message.c_str(), message.length());
                commande = "Enter a command: \n" ;
                write(new_socket, commande.c_str(), commande.length());

                return(1);
            }
        }
    }
    return (0);
}

int CheckClientExiste(std::vector<clien> client_tab, int new_socket)
{
    std::string message;
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (client_tab[i].sd == new_socket)
        {
            write(new_socket, "Welcome back\n", 13);
            if (client_tab[i].password == "")
            {
                write(new_socket, "Enter the password\n", 19);
                return 1;
            }
            else if (client_tab[i].username == "")
            {
                write(new_socket, "Enter your username: ", 21);
                return 1;
            }
            else if (client_tab[i].nickname == "")
            {
                write(new_socket, "Enter your nickname: ", 21);
                return 1;
            }
            else
                write(new_socket, "Enter a command: \n", 18);
            return 1;
        }
    }
    return 0;
}

void redirectFonction(int newsocket, char *buffer, std::vector<clien> client_tab, std::string password)
{
    
}*/
