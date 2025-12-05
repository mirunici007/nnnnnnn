#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "user.h"
#include "operator.h"
#include "usersManager.h"
#include "gestionareCSV.h"
#include "managerCurse.h"
#include "exceptions.h"
#include "utils.h"

using namespace std;

void menuUser(UsersManager &um, ManagerCurse &mc, const string &email, GestionareCSV &gestion) {
    User* userPtr = nullptr;
    for (auto &u : um.users) {
        if (u.getEmail() == email) {
            userPtr = &u;
            break;
        }
    }
    if (!userPtr) {
        cout << "Eroare: user-ul nu a fost gasit." << endl;
        return;
    }

    User &user = *userPtr;

    while (true) {
        cout << "\n~~~MENIU UTILIZATOR~~~\n";
        cout << "1. Schimbare parola\n2. Cauta cursa\n3. Rezervare calatorie\n4. Afisare bilete\n5. Delogare\n";
        int opt = Utils::readInt("Optiune: ");

        if (opt == 1) {
            string newPass;
            cout << "Parola noua: ";
            getline(cin, newPass);
            try {
                um.updatePassword(email, newPass);
                cout << "Succes! Parola a fost schimbata." << endl;
            } catch (const exception &e) {
                cout << "Eroare: " << e.what() << endl;
            }
        }
        else if (opt == 2) {
            string plecare = Utils::normalizeString(Utils::citesteValid("Plecare: ", Utils::validateCity));
            string sosire  = Utils::normalizeString(Utils::citesteValid("Sosire: ", Utils::validateCity));
            string data    = Utils::normalizeDate(Utils::citesteValid("Data (DD/MM/YYYY): ", Utils::validateDate));
            string ora     = Utils::normalizeTime(Utils::citesteValid("Ora (HH:MM): ", Utils::validateTime));

            try {
                bool gasit = false;
                for (auto &c : mc.curse) {
                    if (Utils::normalizeString(c.getLocPlecare()) == plecare &&
                        Utils::normalizeString(c.getLocSosire())  == sosire &&
                        Utils::normalizeDate(c.getData()) == data &&
                        Utils::normalizeTime(c.getOraPlecare()) == ora) {
                        cout << "\n~~~CURSA GASITA~~~\n";
                        cout << "Plecare: " << c.getLocPlecare() << "  Sosire: " << c.getLocSosire()
                             << "  Data: " << c.getData() << "  Ora: " << c.getOraPlecare()
                             << "  Locuri: " << c.getLocuriDisponibile() << endl;
                        gasit = true;
                        break;
                    }
                }
                if (!gasit) throw NotFound("Cursa nu exista!");
            } catch (const NotFound &e) {
                cout << "Eroare: " << e.what() << endl;
            }
        }
        else if (opt == 3) {
            string plecare = Utils::normalizeString(Utils::citesteValid("Plecare: ", Utils::validateCity));
            string sosire  = Utils::normalizeString(Utils::citesteValid("Sosire: ", Utils::validateCity));
            string data    = Utils::normalizeDate(Utils::citesteValid("Data (DD/MM/YYYY): ", Utils::validateDate));
            string ora     = Utils::normalizeTime(Utils::citesteValid("Ora (HH:MM): ", Utils::validateTime));

            try {
                mc.rezervareLoc(plecare, sosire, ora, data);
                Bilet b(user.getID(), plecare, sosire, data, ora);
                user.adaugaBilet(b);
                cout << "Succes: Rezervare efectuata!" << endl;
            } catch (const exception &e) {
                cout << "Eroare: " << e.what() << endl;
            }
        }
        else if (opt == 4) {
            cout << "\n~~~BILETE~~~" << endl;
            user.afiseazaBilete();
        }
        else if (opt == 5) {
            cout << "Utilizator delogat." << endl;
            return;
        }
        else {
            cout << "Eroare: optiune invalida!" << endl;
        }
    }
}

void menuOperator(ManagerCurse &mc, GestionareCSV &gestion) {
    while (true) {
        cout << "\n~~~MENIU OPERATOR~~~\n";
        cout << "1. Adaugare cursa\n2. Stergere cursa\n3. Delogare\n";
        int opt = Utils::readInt("Optiune: ");

        if (opt == 1) {
            string ID = Utils::citesteValid("ID cursa: ", [](const string &s){ if(s.empty()) throw invalid_argument("ID invalid"); });
            string locPlecare = Utils::normalizeString(Utils::citesteValid("Plecare: ", Utils::validateCity));
            string locSosire  = Utils::normalizeString(Utils::citesteValid("Sosire: ", Utils::validateCity));
            string data = Utils::normalizeDate(Utils::citesteValid("Data (DD/MM/YYYY): ", Utils::validateDate));
            string ora = Utils::normalizeTime(Utils::citesteValid("Ora (HH:MM): ", Utils::validateTime));
            int loc = Utils::readInt("Locuri: ");

            try {
                mc.adaugaCursa(ID, locPlecare, locSosire, data, ora, loc);
                gestion.saveCurse("trips.csv", mc.curse);
                cout << "Succes: Cursa adaugata!" << endl;
            } catch (const exception &e) {
                cout << "Eroare: " << e.what() << endl;
            }
        }
        else if (opt == 2) {
            string id = Utils::citesteValid("ID cursa de sters: ", [](const string &s){ if(s.empty()) throw invalid_argument("ID invalid"); });
            try {
                mc.stergeCursa(id);
                gestion.saveCurse("trips.csv", mc.curse);
                cout << "Succes: Cursa stearsa!" << endl;
            } catch (const exception &e) {
                cout << "Eroare: " << e.what() << endl;
            }
        }
        else if (opt == 3) {
            cout << "Operator delogat." << endl;
            return;
        }
        else {
            cout << "Eroare: optiune invalida!" << endl;
        }
    }
}

int main() {
    srand((unsigned)time(nullptr));

    UsersManager um;
    ManagerCurse mc;
    GestionareCSV gestion;
    vector<Operator> operators;

    try { um.loadUsersFromCSV("users.csv"); } catch (...) {}
    try { operators = gestion.loadOperators("operators.csv"); } catch (...) {}
    try { mc.curse = gestion.loadCurse("trips.csv"); } catch (...) {}

    while (true) {
        cout << "\n~~~MENIU PRINCIPAL~~~\n";
        cout << "1. Login User\n2. Adauga cont User\n3. Login Operator\n4. IESIRE\n";
        int opt = Utils::readInt("Optiune: ");

        if (opt == 1) {
            string email = Utils::citesteEmailValid("Email: ");
            string pass;
            cout << "Parola: ";
            getline(cin, pass);

            if (um.loginUser(email, pass)) {
                menuUser(um, mc, email, gestion);
            } else {
                cout << "Eroare: Login esuat." << endl;
            }
        }
        else if (opt == 2) {
            string nume, pren, email, pass;
            cout << "Nume: "; getline(cin, nume);
            cout << "Prenume: "; getline(cin, pren);
            email = Utils::citesteEmailValid("Email: ");
            cout << "Parola: "; getline(cin, pass);

            try {
                um.createUserAccount(nume, pren, email, pass);
                cout << "Succes: Cont creat!" << endl;
            } catch (const exception &e) {
                cout << "Eroare: " << e.what() << endl;
            }
        }
        else if (opt == 3) {
            string email = Utils::citesteEmailValid("Email operator: ");
            string pass;
            cout << "Parola: ";
            getline(cin, pass);

            bool ok = false;
            for (auto &op : operators) {
                if (op.login(email, pass)) { ok = true; break; }
            }

            if (ok) menuOperator(mc, gestion);
            else    cout << "Eroare: Operator invalid!" << endl;
        }
        else if (opt == 4) {
            cout << "Program inchis." << endl;
            break;
        }
        else {
            cout << "Eroare: optiune invalida!" << endl;
        }
    }

    return 0;
}
