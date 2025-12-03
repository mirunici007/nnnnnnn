#ifndef USER_H
#define USER_H

#include <fstream>
#include <vector>
#include "bilet.h"


class User{
    std::string ID;
    std::string lastName;   //nume
    std::string firstName;  //prenume
    std::string email;
    std::string password;

    std::vector<Bilet> bilete;

    public:
    User()=default;
    ~User()=default;
    User(std::string ID, std::string lastName, std::string firstName,
        std::string email, std::string password);

    std::string getID()const;
    std::string getLastName()const;
    std::string getFirstName()const;
    std::string getEmail()const;
    std::string getPassword()const;

    void displayUser()const;

    //de pus in passwrod
    bool verifyPassword(const std::string &password) const;
    //void setPasswordEncrypted(const std::string &passwordEncrypted);
    void setPassword(const std::string &newPassword); 
    
    void adaugaBilet(const Bilet &bilet);
    void afiseazaBilete() const;
};

#endif