#pragma once

#include "irc.hpp"

void msg(User executer, STRING_VECTOR bufferSplit, std::vector<User> users);
void nick(User& executer, STRING_VECTOR bufferSplit, std::vector<User> users);
void quit(User executer);
void ping(User executer, STRING_VECTOR bufferSplit);
void motd(User executer);
void away(User executer, STRING_VECTOR bufferSplit);
void join(User executer, STRING_VECTOR bufferSplit, Server& irc_server);
void help(User executer, STRING_VECTOR bufferSplit, Server& irc_server);
void part (User executer, STRING_VECTOR bufferSplit, Server& irc_server);
