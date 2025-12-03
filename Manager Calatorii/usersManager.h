#ifndef USERSMANAGER_H
#define USERSMANAGER_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <sstream>
#include <stdexcept>
#include <algorithm>

#include "user.h"


class UsersManager{
    std::vector<User> users;
    static std::string generateID();
    public:
    UsersManager()=default;
    ~UsersManager(){};

    bool isEmailValid(const std::string &email)const;
    void createUserAccount(const std::string &lastName, const std::string &firstName, const std::string &email, const std::string &password);

    void deleteUser(const std::string &email);
    void updatePassword(const std::string &email, const std::string &newPassword);

    void addUserToCSV(const std::string &filename, const User &user);
    void loadUsersFromCSV(const std::string &filename);


};

#endif