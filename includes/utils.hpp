#include <vector>
#pragma once

void    print_error (std::string error_message);
bool    CheckClientExists (std::vector<clien> clients, int fd);
void    removeInvisibleChars(char* str);
int     removeStringVector(std::vector<std::string>& myVector, const char* target);
