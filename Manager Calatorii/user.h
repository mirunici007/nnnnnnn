#ifndef USER_H
#define USER_H

#include <fstream>
#include <vector>
#include <string>
#include "bilet.h"

class User{
    std::string ID;
    std::string lastName;   //nume
    std::string firstName;  //prenume
    std::string email;
    std::string password;

    std::vector<Bilet> bilete;

public:
    User() = default;
    ~User() = default;

    User(const std::string& ID, const std::string& lastName, const std::string& firstName,
         const std::string& email, const std::string& password, bool isEncrypted = false);

    std::string getID() const;
    std::string getLastName() const;
    std::string getFirstName() const;
    std::string getEmail() const;
    std::string getPassword() const;

    void setPassword(const std::string &newPassword);
    bool login(const std::string &emailInput, const std::string &passwordInput);

    void adaugaBilet(const Bilet &bilet);
    void afiseazaBilete() const;

    std::vector<Bilet> getBilete() const;
};

#endif
