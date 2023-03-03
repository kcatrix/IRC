#pragma once

#include <vector>
#include <string>
#include "irc.hpp"

void msg(User executer, std::vector<std::string> bufferSplit, std::vector<User> users);
void nick(User& executer, std::vector<std::string> bufferSplit, std::vector<User> users);
void quit(User executer);
void ping(User executer, char *buffer);
void modt(User executer);
void away(User executer, char *buffer);
void join(User executer, std::vector<std::string> bufferSplit, Server& irc_server);
