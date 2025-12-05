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
#include <fstream>

using namespace std;

static inline std::string trim(const std::string &s) {
    size_t start = 0;
    while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) ++start;
    size_t end = s.size();
    while (end > start && isspace(static_cast<unsigned char>(s[end-1]))) --end;
    return s.substr(start, end - start);
}

string UsersManager::generateID() {
    string ID = "ID";
    int nrGenerat = rand() % 10000000 + 100000;
    ID += to_string(nrGenerat);
    return ID;
}

bool UsersManager::isEmailValid(const string &email) {
    const char* e = email.c_str();
    int len = strlen(e);
    if (len < 5) return false;
    const char* poz = strchr(e, '@');
    if (!poz) return false;
    if (strchr(poz + 1, '@')) return false;
    if (poz == e || poz == e + len - 1) return false;
    const char* dot = strchr(poz, '.');
    if (!dot) return false;
    if (dot == poz + 1) return false;
    if (dot == e + len - 1) return false;
    if (strlen(poz + 1) < 3) return false;
    return true;
}

void UsersManager::createUserAccount(const string &lastName, const string &firstName, const string &email, const string &password) {
    if (!isEmailValid(email)) {
        throw InvalidData("Email invalid!");
    }

    for (auto &user : users) {
        if (user.getEmail() == email) {
            throw InvalidData("Exista deja un cont inregistrat cu acest email!");
        }
    }

    auto strength = Password::checkPasswordStrength(password);
    if (strength == Password::WEAK) {
        throw WeakPassword("Parola este prea slaba");
    } else if (strength == Password::OK) {
        cout << "Parola este medie. Pentru o securitate mai buna, va recomandam sa alegeti o parola mai puternica." << endl;
    }

    string ID = generateID();
    User newUser(ID, lastName, firstName, email, password, false);

    addUserToCSV("users.csv", newUser);
    users.push_back(newUser);

    cout << "Cont creat cu succes!" << endl;
}

void UsersManager::addUserToCSV(const string &filename, const User &user) {
    bool needHeader = false;
    {
        std::ifstream in(filename);
        if (!in.is_open()) {
            needHeader = true;
        } else {
            in.seekg(0, ios::end);
            if (in.tellg() == 0) needHeader = true;
        }
    }

    ofstream file(filename, ios::out | ios::app);
    if (!file.is_open()) {
        throw InvalidData("Eroare la deschiderea fisierului " + filename);
    }

    if (needHeader) {
        file << "ID,Last,First,Email,Password\n";
    }

    file << user.getID() << ","
         << user.getLastName() << ","
         << user.getFirstName() << ","
         << user.getEmail() << ","
         << user.getPassword() << endl;

    file.close();
}

void UsersManager::loadUsersFromCSV(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        // nu aruncam neaparat — caller poate decide; dar urmam comportamentul anterior
        throw InvalidData("Eroare la deschiderea fisierului pentru citire: " + filename);
    }

    string line;
    bool firstLine = true;
    while (getline(file, line)) {
        if (line.empty()) continue;

        // detectam header: daca prima coloana contine "ID" (insensitiv la case)
        if (firstLine) {
            string tmp = trim(line);
            // transformam tmp la lowercase simplu
            string tmpLower = tmp;
            transform(tmpLower.begin(), tmpLower.end(), tmpLower.begin(), [](unsigned char c){ return std::tolower(c); });
            if (tmpLower.rfind("id,", 0) == 0 || tmpLower == "id,last,first,email,password") {
                firstLine = false;
                continue; // skip header
            }
            // daca nu e header, nu sarim; procesam prima linie normal
            firstLine = false;
        }

        stringstream ss(line);
        string id, lastName, firstName, email, password;

        getline(ss, id, ',');
        getline(ss, lastName, ',');
        getline(ss, firstName, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');

        id = trim(id);
        lastName = trim(lastName);
        firstName = trim(firstName);
        email = trim(email);
        password = trim(password); // foarte important: elimina '\r' sau spatii

        // folosim constructorul cu isEncrypted = true (parola din CSV este deja criptata)
        users.emplace_back(User(id, lastName, firstName, email, password, true));
    }

    file.close();
}

void UsersManager::deleteUser(const string &email) {
    auto it = find_if(users.begin(), users.end(), [&](const User &u){ return u.getEmail() == email; });
    if (it == users.end()) {
        throw NotFound("Utilizatorul inregistrat cu acest email nu exista in baza de date!");
    }
    users.erase(it);

    ofstream file("users.csv", ios::out | ios::trunc);
    if (!file.is_open()) {
        throw InvalidData("Eroare la deschiderea fisierului pentru scriere: users.csv");
    }

    // scriem header in fisierul rescris
    file << "ID,Last,First,Email,Password\n";
    for (auto &user : users) {
        file << user.getID() << ","
             << user.getLastName() << ","
             << user.getFirstName() << ","
             << user.getEmail() << ","
             << user.getPassword() << "\n";
    }

    file.close();
    cout << "Utilizator sters cu succes!" << endl;
}

void UsersManager::updatePassword(const string &email, const string &newPassword) {
    bool found = false;
    for (auto &user : users) {
        if (user.getEmail() == email) {
            user.setPassword(newPassword);
            found = true;
            break;
        }
    }

    if (!found) {
        throw NotFound("Utilizatorul inregistrat cu acest email nu exista in baza de date!");
    }

    ofstream file("users.csv", ios::out | ios::trunc);
    if (!file.is_open()) {
        throw InvalidData("Eroare la deschiderea fisierului pentru scriere: users.csv");
    }

    file << "ID,Last,First,Email,Password\n";
    for (auto &user : users) {
        file << user.getID() << ","
             << user.getLastName() << ","
             << user.getFirstName() << ","
             << user.getEmail() << ","
             << user.getPassword() << "\n";
    }

    file.close();
    cout << "Parola actualizata cu succes!" << endl;
}

bool UsersManager::loginUser(const string &email, const string &password) {
    string emTrim = trim(email);
    string pwTrim = trim(password);

    for (auto &u : users) {
        if (u.getEmail() == emTrim && Password::verifyPassword(pwTrim, u.getPassword())) {
            cout << "Autentificare reusita!\n";
            return true;
        }
    }
    cout << "Email sau parola gresita!\n";
    return false;
}
