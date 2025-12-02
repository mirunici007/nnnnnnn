#ifndef USER_H
#define USER_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>


class User{
    std::string ID;
    std::string lastName;   //nume
    std::string firstName;  //prenume
    std::string email;
    std::string password;

    public:
    User()=default;
    ~User(){};
    User(std::string ID, std::string lastName, std::string firstName, 
        std::string email, std::string password);

    std::string getID()const;
    std::string getLastName()const;
    std::string getFirstName()const;
    std::string getEmail()const;
    std::string getPassword()const;

    void displayUser()const;

    bool verifyPassword(const std::string &password) const;
    void setPasswordEncrypted(const std::string &passwordEncrypted);
    void setPassword(const std::string &newPassword); 
    
    //static void createUser()
};

#endif