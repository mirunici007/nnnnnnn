#ifndef USERSMANAGER_H
#define USERSMANAGER_H

#include <fstream>
#include <vector>
#include "user.h"

class UsersManager{
    static std::string generateID();
public:

    std::vector<User> users;

    UsersManager() = default;
    ~UsersManager() = default;

    static bool isEmailValid(const std::string &email);
    void createUserAccount(const std::string &lastName, const std::string &firstName, const std::string &email, const std::string &password);

    void deleteUser(const std::string &email);
    void updatePassword(const std::string &email, const std::string &newPassword);

    static void addUserToCSV(const std::string &filename, const User &user);
    void loadUsersFromCSV(const std::string &filename);

    bool loginUser(const std::string &email, const std::string &password);
};

#endif
