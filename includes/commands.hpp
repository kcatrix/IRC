#pragma once

#include "irc.hpp"

void msg(User executer, STRING_VECTOR bufferSplit, USER_VECTOR users, Server& irc_server);
void nick(User& executer, STRING_VECTOR bufferSplit, USER_VECTOR users);
void quit(User executer);
void ping(User executer, STRING_VECTOR bufferSplit);
void motd(User executer);
void away(User executer, STRING_VECTOR bufferSplit);
void join(User executer, STRING_VECTOR bufferSplit, Server& irc_server);
void help(User executer, STRING_VECTOR bufferSplit, STRING_VECTOR commands_list);
void part (User executer, STRING_VECTOR bufferSplit, Server& irc_server);
void list (User executer, CHANNEL_VECTOR& channels);
void names (User executer, STRING_VECTOR bufferSplit, Server& irc_server);
void kick (User executer, STRING_VECTOR bufferSplit, Server& irc_server);
void ban (User executer, STRING_VECTOR bufferSplit, Server& irc_server);
void op (User executer, STRING_VECTOR bufferSplit, Server& irc_server);
void deop (User executer, STRING_VECTOR bufferSplit, Server& irc_server);
void invite (User executer, STRING_VECTOR bufferSplit, Server& irc_server);
