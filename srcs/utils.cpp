#include "../includes/irc.hpp"

void    print_message (int sd, std::string message) {
    write (sd, message.c_str (), message.length ());
}

void    print_error (std::string error_message) {
    std::cout << error_message << std::endl;
    exit (EXIT_FAILURE);
}

STRING_VECTOR splitString (std::string& str) {
    STRING_VECTOR result;
    std::string::size_type start = 0;
    std::string::size_type end = str.find (" ");

    str.erase (str.length () - 1, 1);
    while (end != std::string::npos) {
        if (end > start) {
            result.push_back (str.substr (start, end - start));
        }
        start = end + 1;
        end = str.find(" ", start);
    }
    if (start < str.size ()) {
        result.push_back (str.substr(start));
    }
    result.push_back ("");
    return result;
}
