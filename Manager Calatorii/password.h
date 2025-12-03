#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>

#define PASSWORD_KEY   0x5A
#define PASSWORD_SHIFT 4

class Password{
    public:
    Password()=default;
    ~Password()=default;
    enum Strength{
        WEAK,
        OK,
        GOOD
    };

    friend class Operator;
    friend class UsersManager;

    //bool checkPassword(const string &originalPassword);
    static Strength checkPasswordStrength(const std::string &password);

    static std::string encryptCaesar(const std::string &originalPassword, char key, int shift);
    static std::string decryptCaesar(const std::string &encryptedPassword, char key, int shift);

    static bool verifyPassword(const std::string &plainPassword, const std::string &encryptedpassword);

};

#endif