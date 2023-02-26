#include "../includes/utils.hpp"
#include <iostream>

void    print_error (std::string error_message) {
    std::cerr << error_message << std::endl;
    exit (EXIT_FAILURE);
}
