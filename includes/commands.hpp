#pragma once

#include <vector>
#include "irc.hpp"

void msg(User executer, char *buffer, std::vector<User> users);
void nick(User executer, char *buffer, std::vector<User> *users);
void quit(User executer);
void ping(User executer, char *buffer);
void modt(User executer);
void away(User executer, char *buffer);
