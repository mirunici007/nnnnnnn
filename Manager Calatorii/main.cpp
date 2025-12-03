#include <iostream>
#include <vector>
#include <algorithm>
#include "gestionareCSV.h"
#include "password.h"
#include "usersManager.h"

using namespace std;

int main() {
    GestionareCSV gestionareCSV;
    vector<User> users;

    // Încarcă utilizatorii existenți din CSV
    try {
        users = gestionareCSV.loadUsers("users.csv");
    } catch (const exception &e) {
        cout << "Nu s-au putut încărca utilizatorii (fisierul poate să nu existe).\n";
    }

    cout << "=== Aplicatie de gestionare a calatoriilor ===" << endl;

    while (true) {
        cout << "\nAlegeti o optiune:\n";
        cout << "1. Login ca utilizator\n";
        cout << "2. Adauga cont utilizator\n";
        cout << "3. Sterge cont utilizator\n";
        cout << "4. Schimba parola\n";
        cout << "5. Iesi din aplicatie\n";

        int option;
        cin >> option;
        if(option < 1 || option > 5) {
            cout << "Optiune invalida! Introduceti din nou.\n";
            continue;
        }
        if(option == 5) break;

        string email, password, firstName, lastName, newPass;

        switch(option) {
            case 1: // Login
                while (true) {
                    cout << "Email: "; cin >> email;
                    cout << "Parola: "; cin >> password;

                    auto it = find_if(users.begin(), users.end(),
                                      [&](User &u){ return u.getEmail() == email &&
                                              Password::verifyPassword(password, u.getPassword()); });
                    if(it != users.end()){
                        cout << "Login reusit!\n";
                        break;
                    } else {
                        cout << "Email sau parola gresita! Incercati din nou.\n";
                    }
                }
                break;

            case 2: // Adauga cont
                cout << "Prenume: "; cin >> firstName;
                cout << "Nume: "; cin >> lastName;

                // Validare email
                while(true){
                    cout << "Email: "; cin >> email;

                    auto it = find_if(users.begin(), users.end(),
                                      [&](User &u){ return u.getEmail() == email; });

                    if(it != users.end()){
                        cout << "Exista deja un cont cu acest email! Incercati alt email.\n";
                        continue;
                    }

                    if(!UsersManager::isEmailValid(email)){
                        cout << "Email invalid! Incercati din nou.\n";
                        continue;
                    }

                    break;
                }

                // Validare parola
                while(true){
                    cout << "Parola: "; cin >> password;
                    auto strength = Password::checkPasswordStrength(password);

                    if(strength == Password::WEAK){
                        cout << "Parola este prea slaba! Incercati din nou.\n";
                        continue;
                    } else if(strength == Password::OK) {
                        cout << "Parola este medie. Pentru securitate mai buna, alegeti o parola mai puternica.\n";
                    }

                    break;
                }

                // Creare user și salvare
                try {
                    string ID = "ID" + to_string(rand()%10000000+100000);
                    User newUser(ID, lastName, firstName, email, password);
                    users.push_back(newUser);

                    gestionareCSV.saveUsers("users.csv", users);

                    cout << "Cont creat si salvat in users.csv!\n";
                } catch(const exception &e){
                    cout << "Eroare: " << e.what() << endl;
                }
                break;

            case 3: // Sterge cont
                while(true){
                    cout << "Email utilizator de sters: "; cin >> email;
                    auto it = find_if(users.begin(), users.end(),
                                      [&](User &u){ return u.getEmail() == email; });

                    if(it != users.end()){
                        users.erase(it);
                        gestionareCSV.saveUsers("users.csv", users);
                        cout << "Utilizator sters cu succes!\n";
                        break;
                    } else {
                        cout << "Nu exista utilizator cu acest email! Incercati din nou.\n";
                    }
                }
                break;

            case 4: // Schimba parola
                while(true){
                    cout << "Email: "; cin >> email;
                    auto it = find_if(users.begin(), users.end(),
                                      [&](User &u){ return u.getEmail() == email; });

                    if(it != users.end()){
                        cout << "Noua parola: "; cin >> newPass;
                        it->setPassword(newPass);
                        gestionareCSV.saveUsers("users.csv", users);
                        cout << "Parola actualizata cu succes!\n";
                        break;
                    } else {
                        cout << "Nu exista utilizator cu acest email! Incercati din nou.\n";
                    }
                }
                break;
        }
    }

    return 0;
}
