#include "../includes/irc.hpp"

void    identify (User& executer, std::string new_password) {
    if (executer.logInPwd == new_password) {
        print_message (executer.sd, "This is already your password.\n");
        return;
    }
    else {
        executer.logInPwd = new_password;
        print_message (executer.sd, "Your password was changed to " + new_password + ".\n");
    }
}
