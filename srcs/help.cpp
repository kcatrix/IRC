#include "../includes/irc.hpp"

void    printCommandsList (int sd, STRING_VECTOR commands_list) {
    for (STRING_ITERATOR it = commands_list.begin (); it != commands_list.end (); it++)
        print_message (sd, it->erase (0, 1) + "\n");
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

void    printMotd (int sd) {
    print_message (sd, "Use: /motd.\nDisplay the message of the day of your IRC server.\n");
}

void    printAway (int sd) {
    print_message (sd, "Use: /away <afk message>.\nAutomatically reply to a user sending you a private message with your afk message.\n");
}

void    printJoin (int sd) {
    print_message (sd, "Use: /join <channel>.\nJoin a channel. If the channel doesn't exist, you will create it and be automatically promoted to operator of this channel.\n");
}

void    printPart (int sd) {
    print_message (sd, "Use: /part <channel>.\nLeave a channel.\n");
}

void    printNames (int sd) {
    print_message (sd, "Use: /names <channel1> <channel2>.\nList the users present in the listed channels.\n");
}

void    printList (int sd) {
    print_message (sd, "Use: /list.\nList the channels on the server.\n");
}

void    printHelp (int sd) {
    print_message (sd, "Use: /help <command>.\nDisplay the function of the command. If nothing is entered, a list of available commands will be displayed.\n");
}

void    printKick (int sd) {
    print_message (sd, "Use: /kick <channel> <nickname> <reason>.\nKick a user from a channel. If a reason is given, it will be displayed to the user that was kicked.\n");
}

void    printBan (int sd) {
    print_message (sd, "Use: /ban <channel> <nickname>.\nBan a user from the channel\n");
}

void    printOp (int sd) {
    print_message (sd, "Use: /op <channel> <nickname>.\nPromote a user to operator status in a channel.\n");
}

void    printDeop (int sd) {
    print_message (sd, "Use: /deop <channel> <nickname>.\nDemote a user from operator status in a channel.\n");
}

void    printInvite (int sd) {
    print_message (sd, "Use: /invite <channel> <nickname>.\nInvite a user to a channel.\n");
}

void    printIgnore (int sd) {
    print_message (sd, "Use: /ignore <nickname>.\nMake all messages from a user invisible to you, in a channel or in private.\n");
}

void    printAccept (int sd) {
    print_message (sd, "Use: /accept <nickname>.\nRemove the ignore status of a user.\n");
}

void    printIdentify (int sd) {
    print_message (sd, "Use: /identify <password>.\nAssign a password to your nickname.\n");
}

void    printHelp (int sd, std::string command) {
    if (command == "pvtmsg" or command == "w")
        printPvtmsg (sd);
    else if (command == "nick")
        printNick (sd);
    else if (command == "quit")
        printQuit (sd);
    else if (command == "kick")
        printKick (sd);
    else if (command == "ban")
        printBan (sd);
    else if (command == "op")
        printOp (sd);
    else if (command == "deop")
        printDeop (sd);
    else if (command == "invite")
        printInvite (sd);
    else if (command == "ignore")
        printIgnore (sd);
    else if (command == "accept")
        printAccept (sd);
    else if (command == "motd")
        printMotd (sd);
    else if (command == "away")
        printAway (sd);
    else if (command == "join")
        printJoin (sd);
    else if (command == "part")
        printPart (sd);
    else if (command == "names")
        printNames (sd);
    else if (command == "list")
        printList (sd);
    else if (command == "help")
        printHelp (sd);
    else if (command == "identify")
        printIdentify (sd);
}

void    help (User executer, STRING_VECTOR bufferSplit, STRING_VECTOR commands_list) {
    if (bufferSplit[1].empty () == 1)
        printCommandsList (executer.sd, commands_list);
    else
        printHelp (executer.sd, bufferSplit[1]);
}
