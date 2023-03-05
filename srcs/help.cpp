#include "../includes/irc.hpp"

void    printCommandsList (int sd, STRING_VECTOR commands_list) {
    for (STRING_ITERATOR it = commands_list.begin (); it != commands_list.end (); it++)
        print_message (sd, (*it).erase (0, 1) + "\n");
}

void    printPvtmsg (int sd) {
    print_message (sd, "Use: /w <nickname>.\nSend a private message (whisper) to a user.\n");
}

void    printNick (int sd) {
    print_message (sd, "Use: /nick <nickname>.\nChange your current nickname.\n");
}

void    printQuit (int sd) {
    print_message (sd, "Use: /quit <reason>.\nDisconnect from the server and notifies other users sharing at least one channel with you. If you write a reason, it will be sent along with the notification.\n");
}

/*void    printPing (int sd) {
    print_message (sd, "Use: /w <nickname>.\nSend a private message (whisper) to the user <nickname>.\n");
}*/

void    printMotd (int sd) {
    print_message (sd, "Use: /motd.\nDisplays the message of the day of your IRC server.\n");
}

void    printAway (int sd) {
    print_message (sd, "Use: /away <afk message>.\nAutomatically reply to a user sending you a private message with your afk message.\n");
}

void    printJoin (int sd) {
    print_message (sd, "Use: /join <#channel>.\nJoin a channel. If the channel doesn't exist, you will create it and be automatically promoted to operator of this channel.\n");
}

void    printHelp (int sd) {
    print_message (sd, "Use: /help <command>.\nDisplays the function of the command. If nothing is entered, a list of available commands will be displayed.\n");
}

void    printHelp (int sd, std::string command) {
    if (command == "w")
        printPvtmsg (sd);
    if (command == "nick")
        printNick (sd);
    if (command == "quit")
        printQuit (sd);
    if (command == "motd")
        printMotd (sd);
    if (command == "away")
        printAway (sd);
    if (command == "join")
        printJoin (sd);
    if (command == "help")
        printHelp (sd);
}

void    help (User executer, STRING_VECTOR bufferSplit, Server& irc_server) {
    if (bufferSplit[1].empty ())
        printCommandsList (executer.sd, irc_server.commands_list);
    else
        printHelp (executer.sd, bufferSplit[0]);
    return;
}
