#pragma once

#include <vector>
#include <string>
#include "irc.hpp"

void msg(User executer, std::vector<std::string> bufferSplit, std::vector<User> users);
void nick(User& executer, std::vector<std::string> bufferSplit, std::vector<User> users);
void quit(User executer);
void ping(User executer, std::vector<std::string> bufferSplit);
void motd(User executer);
void away(User executer, std::vector<std::string> bufferSplit);
void join(User executer, std::vector<std::string> bufferSplit, Server& irc_server);
void help(User executer, Server& irc_server);
