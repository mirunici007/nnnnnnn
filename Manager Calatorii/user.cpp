#include "user.h"
#include "password.h"

using namespace std;

User::User(const string ID,
        const string lastName,
        const string firstName,
        const string email,
        const string password): ID(ID), lastName(lastName), firstName(firstName), email(email), password(password) {
    setPassword(password);
}

void User::setPassword(const string &newPassword){
    password = Password::encryptCaesar(newPassword, PASSWORD_KEY, PASSWORD_SHIFT);
}

string User::getID()const{
    return this->ID;
}
string User::getLastName()const{
    return this->lastName;
}
string User::getFirstName()const{
    return this->firstName;
}
string User::getEmail()const{
    return this->email;
}
string User::getPassword()const{
    return this->password;
}


void User::adaugaBilet(const Bilet &bilet) {
    bilete.push_back(bilet);
}

void User::afiseazaBilete() const {
    for (auto &bilet: bilete) {
        bilet.afisareDetaliiBilet();
    }
}

/*User User::gasesteUser(const std::string &email) {
    User user;

    vector<User> users = loadUsers("users.csv");
}*/

bool User::login(const string &emailInput, const string &passwordInput){
    if(email != emailInput)
        return false;

    return Password::verifyPassword(passwordInput, password);
}