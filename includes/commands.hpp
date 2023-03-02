#pragma once

#include "irc.hpp"

void msg(int newsocket, char *buffer, std::vector<clien> clients);
void nick(int newsocket, char *buffer, std::vector<clien> *clients);
void quit(int newsocket, std::vector<clien> clients);
