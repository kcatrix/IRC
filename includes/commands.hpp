#pragma once

#include <vector>
#include "irc.hpp"

void msg(clien executer, char *buffer, std::vector<clien> clients);
void nick(clien executer, char *buffer, std::vector<clien> *clients);
void quit(clien executer);
void ping(clien executer, char *buffer);
void modt(clien executer);
void away(clien executer, char *buffer);
