#include "user.h"
#include "password.h"

using namespace std;

User::User(string ID,
        string lastName,
        string firstName,
        string email,
        string password): ID(ID), lastName(lastName), firstName(firstName), email(email), password(password) {}

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

//trebuie verificare autetificare pt siguranta!!!!!
void User::displayUser()const{
    cout<<"ID: "<<this->ID<<endl;
    cout<<"Nume: "<<this->lastName<<endl;
    cout<<"Prenume: "<<this->firstName<<endl;
    cout<<"Email: "<<this->email<<endl;
    cout<<"Parola: "<<this->password<<endl;
}

//bool verifyPassword(const string &password) const;

/*void User::setPasswordEncrypted(const std::string &passwordEncrypted) {
    password = Password::encryptCaesar(passwordEncrypted, PASSWORD_KEY, PASSWORD_SHIFT);
}*/

void User::setPassword(const std::string &newPassword) {
    this->password = newPassword; // dacă vrei să salvezi direct parola
}

void User::adaugaBilet(const Bilet &bilet) {
    bilete.push_back(bilet);
}

void User::afiseazaBilete() const {
    for (auto &bilet: bilete) {
        bilet.afisareDetaliiBilet();
    }
}