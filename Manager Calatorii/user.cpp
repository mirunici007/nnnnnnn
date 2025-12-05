#include "user.h"
#include "password.h"
#include "gestionareCSV.h"

using namespace std;

User::User(const string& ID,
           const string& lastName,
           const string& firstName,
           const string& email,
           const string& password,
           bool isEncrypted) : ID(ID), lastName(lastName), firstName(firstName), email(email)
{
    if (isEncrypted) {
        this->password = password;
    } else {
        setPassword(password);
    }
}

void User::setPassword(const string &newPassword){
    password = Password::encryptCaesar(newPassword, PASSWORD_KEY, PASSWORD_SHIFT);
}

string User::getID() const {
    return ID;
}

string User::getLastName() const {
    return lastName;
}

string User::getFirstName() const {
    return firstName;
}

string User::getEmail() const {
    return email;
}

string User::getPassword() const {
    return password;
}

bool User::login(const string &emailInput, const string &passwordInput){
    if(email != emailInput)
        return false;

    return Password::verifyPassword(passwordInput, password);
}

void User::adaugaBilet(const Bilet &bilet) {
    bilete.push_back(bilet);
    GestionareCSV gestion;
    gestion.appendBilet("bilete.csv", bilet);
}

void User::afiseazaBilete() const {
    for (auto &bilet: bilete) {
        bilet.afisareDetaliiBilet();
    }
}

vector<Bilet> User::getBilete() const {
    return bilete;
}
