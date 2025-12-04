#include "usersManager.h"
#include "password.h"
#include "exceptions.h"

#include <random>
#include <ctime>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>

using namespace std;

string UsersManager::generateID(){
    string ID="ID";

    int nrGenerat = rand() % 10000000 + 100000;
    ID += to_string(nrGenerat);

    return ID;
}

bool UsersManager::isEmailValid(const string &email) {
    const char* e = email.c_str();
    int len = strlen(e);

    if (len < 5) return false;

    const char* poz = strchr(e, '@');
    if (!poz) {
        return false; 
    }

    if (strchr(poz + 1, '@')){
        return false; //daca exosta 2 de @

    }

    if (poz == e || poz == e + len - 1){
        return false; //daca @ e primul sau ultimul caracter
    }

    const char* dot = strchr(poz, '.');

    if (!dot){
        return false;}
    if (dot == poz + 1){
        return false; 
    }
    if (dot == e + len - 1){
        return false; //se termină cu .
    }

    if (strlen(poz + 1) < 3){
        return false;   //verifica domeniul
    }

    return true;
}

void UsersManager::createUserAccount(const string &lastName, const string &firstName, const string &email, const string &password){
    if(!isEmailValid(email)){
        throw InvalidData("Email invalid");
    }

    //verificare parola la creare cont!!!!!!!+criptareeeee

    for(auto &user: users){
        if(user.getEmail()==email){
            throw InvalidData("Exista deja un cont inregistrat cu acest email!");
        }
    }

    auto strength = Password::checkPasswordStrength(password);
        if(strength == Password::WEAK){
            throw WeakPassword("Parola este prea slaba");
        }
        else if(strength == Password::OK){
            cout<<"Parola este de forta medie. Pentru o securitate mai buna, va recomandam sa alegeti o parola mai puternica."<<endl;
        }

    string ID = generateID();
    User newUser(ID, lastName, firstName, email, password);

    addUserToCSV("users.csv", newUser);
    users.push_back(newUser);

    cout<<"Cont creat cu succes!"<<endl;

}

void UsersManager::addUserToCSV(const string &filename, const User &user){
    ofstream file;

    file.open(filename, ios::out | ios::app);
    if(!file.is_open()){
        throw InvalidData("Eroare la deschiderea fisierului pentru scriere: " + filename);
    }

    file<<user.getID()<<","
        <<user.getLastName()<<","
        <<user.getFirstName()<<","
        <<user.getEmail()<<","
        <<user.getPassword()<<endl;

    file.close();
}

void UsersManager::loadUsersFromCSV(const string &filename){
    ifstream file(filename);
    if(!file.is_open()){
        throw InvalidData("Eroare la deschiderea fisierului pentru citire: " + filename);
    }

    string line;
    bool isFirstLine = true;
    while(getline(file, line)){
        if(isFirstLine){
            isFirstLine = false;
            continue; // sărim header-ul
        }

        stringstream ss(line);
        string id, lastName, firstName, email, password;

        getline(ss, id, ',');
        getline(ss, lastName, ',');
        getline(ss, firstName, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');

        // eliminăm spațiile eventuale
        id.erase(0, id.find_first_not_of(" \t\n\r"));
        lastName.erase(0, lastName.find_first_not_of(" \t\n\r"));
        firstName.erase(0, firstName.find_first_not_of(" \t\n\r"));
        email.erase(0, email.find_first_not_of(" \t\n\r"));
        password.erase(0, password.find_first_not_of(" \t\n\r"));

        users.emplace_back(User(id, lastName, firstName, email, password));
    }

    file.close();
}



void UsersManager::deleteUser(const string &email){
    auto it = find_if(users.begin(), users.end(), [&](const User &u){ return u.getEmail() == email; });
    if (it == users.end()){
        throw NotFound("Utilizatorul inregistrat cu acest email nu exista in baza de date!");
    }
    users.erase(it);

    ofstream file;
    file.open("users.csv", ios::out | ios::trunc);
    if(!file.is_open()){
        throw InvalidData("Eroare la deschiderea fisierului pentru scriere: users.csv");
    }

    for(auto &user: users){
        file<<user.getID()<<","
            <<user.getLastName()<<","
            <<user.getFirstName()<<","
            <<user.getEmail()<<","
            <<user.getPassword()<<endl;
    }

    file.close();
    cout<<"Utilizator sters cu succes!"<<endl;
}

void UsersManager::updatePassword(const string &email, const string &newPassword){
    bool found=false;

    for(auto &user: users){
        if(user.getEmail() == email){
            user.setPassword(newPassword);
            found = true;
            break;
        }
    }

    if(!found){
        throw NotFound("Utilizatorul inregistrat cu acest email nu exista in baza de date!");
    }

    ofstream file;
    file.open("users.csv", ios::out | ios::trunc);
    if(!file.is_open()){
        throw InvalidData("Eroare la deschiderea fisierului pentru scriere: users.csv");
    }

    for(auto &user: users){
        file<<user.getID()<<","
            <<user.getLastName()<<","
            <<user.getFirstName()<<","
            <<user.getEmail()<<","
            <<user.getPassword()<<endl;
    }

    file.close();
    cout<<"Parola actualizata cu succes!"<<endl;
}

bool UsersManager::loginUser(const string &email, const string &password) {
    for(auto &u : users) {
        if(u.getEmail() == email && Password::verifyPassword(password, u.getPassword())) {
            cout << "Autentificare reusita!\n";
            return true;
        }
    }
    cout << "Email sau parola gresita!\n";
    return false;
}
