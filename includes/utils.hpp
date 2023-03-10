#pragma once

# include "irc.hpp"

void    		print_error (std::string error_message);
void			print_message (int sd, std::string message);
STRING_VECTOR   splitString (std::string& string);
