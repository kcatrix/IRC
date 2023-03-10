#include "../includes/irc.hpp"

User    findUser (std::string nickname, USER_VECTOR users) {
    for (USER_ITERATOR user = users.begin (); user != users.end (); user++) {
        if (user->nickname == nickname)
            return *user;
    }
    return User ();
}

static void removecompare (USER_VECTOR &users, std::string compare) {
    for (USER_ITERATOR user = users.begin (); user != users.end (); user++) {
        if (user->nickname == compare) {
            user->nickname = "";
            return;
        }
    }
}

void    checkUserPwd (User& known_user, std::string entry) {
    if (known_user.logInPwd == "")
        known_user.info = USERPWD_OK;
    else if (known_user.logInPwd == entry)
        known_user.info = USERPWD_OK;
    else
        known_user.info = WRONG_USERPWD;
}

void    checkServPwd (User& new_user, std::string entry, std::string password) {
    if (entry == password)
        new_user.info = SERVPWD_OK;
    else
        new_user.info = WRONG_SERVPWD;
}

void    setUsername (User& new_user, std::string username) {
    new_user.username = username;
    new_user.info = WELCOME;
}


void    setNickname (User& new_user, std::string entry, Server& irc_server) {
    User    compare = findUser (entry, irc_server.users);

    if (compare.sd == -1 || compare.sd == -2)
        new_user.info = NICK_TAKEN;
    else if (isalpha (entry[0]) == 0)
        new_user.info = INVALID_NICK;
    else if (compare.nickname.empty () == 1) {
        new_user.nickname = entry;
        new_user.online = true;
        new_user.info = NEW_USER;
    }
    else {
        if (compare.online == true)
            new_user.info = NICK_TAKEN;
        else {
            new_user = compare;
            removecompare(irc_server.users, compare.nickname);
            new_user.online = true;
            new_user.info = KNOWN_USER;
        }
    }
}

void    readInfo (User& user, STRING_VECTOR bufferSplit, Server& irc_server) {
    if (user.info == ENTER_SERVPWD)
        checkServPwd (user, bufferSplit[0], irc_server.getPassword ());
    else if (user.info == SERVPWD_OK)
        setNickname (user, bufferSplit[0], irc_server);
    else if (user.info == KNOWN_USER)
        checkUserPwd (user, bufferSplit[0]);
    else if (user.info == NEW_USER)
        setUsername (user, bufferSplit[0]);
}

void    askInput (const int sd, int& info_status);

void    createUser (int new_socket, USER_VECTOR& users, int& max_sd, int& number_of_users) {
    User new_user (new_socket);
    if (number_of_users >= MAX_USERS) {
        print_message (new_socket, "Too many users on the server.\n");
        close (new_socket);
        return;
    }
    std::cout << "A new user joined the server." << std::endl;
    fcntl (new_socket, F_SETFL, O_NONBLOCK);
    users.push_back (new_user);
    askInput (users.back ().sd, users.back ().info);
    max_sd = std::max (max_sd, new_socket);
    number_of_users++;
}
