#ifndef PASSWORD_H
#define PASSWORD_H

#include <iostream>
#include <cstring>
#include <string>

class Password{
    public:
    Password()=default;
    ~Password(){};
    enum Strength{
        WEAK,
        OK,
        GOOD
    };

    //void setPassword(const string &newPassword);

    //bool checkPassword(const string &originalPassword);
    static Strength checkPasswordStrength(const std::string &password);

    static std::string encryptCaesar(const std::string &originalPassword, char key, int shift);
    static std::string decryptCaesar(const std::string &encryptedPassword, char key, int shift);
};

#endif