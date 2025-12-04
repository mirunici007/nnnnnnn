// main.cpp (înlocuiește fișierul existent)
#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include "user.h"
#include "operator.h"
#include "usersManager.h"
#include "gestionareCSV.h"
#include "managerCurse.h"
#include "exceptions.h"

using namespace std;

// ---------------- VALIDARE EMAIL ----------------
bool emailValid(const string &email) {
    size_t at = email.find('@');
    size_t dot = email.find('.', at + 1);

    return at != string::npos &&
           dot != string::npos &&
           at > 0 &&
           dot < email.size() - 1;
}

string citesteEmailValid(const string &prompt) {
    string email;
    while (true) {
        cout << prompt;
        getline(cin, email);

        if (emailValid(email))
            return email;

        cout << "✘ Format email invalid! Reintroduceti.\n";
    }
}

// Helper — citește un int valid din stdin (cu prompt)
int readInt(const string &prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        } else {
            cout << "Input invalid — introduceți un număr.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// ---------------- MENIU USER ----------------
void menuUser(UsersManager &um, ManagerCurse &mc, const string &email) {
    while (true) {
        cout << "\n===== MENIU UTILIZATOR =====\n";
        cout << "1. Schimbare parola\n";
        cout << "2. Cauta cursa\n";
        cout << "3. Rezervare calatorie\n";
        cout << "4. Afisare bilete\n";
        cout << "5. Delogare\n";
        int opt = readInt("Alegere: ");

        if (opt == 1) {
            string newPass;
            cout << "Parola noua: ";
            getline(cin, newPass);
            try {
                um.updatePassword(email, newPass);
                cout << "Parola schimbata cu succes.\n";
            } catch (const exception &e) {
                cout << "Eroare: " << e.what() << endl;
            }
        }
        else if (opt == 2) {
            string plecare, sosire, ora, data;
            cout << "Introduceți detaliile cursei (Data: DD/MM/YYYY, Ora: HH:MM)\n";
            cout << "Plecare: "; getline(cin, plecare);
            cout << "Sosire : "; getline(cin, sosire);
            cout << "Data   : "; getline(cin, data);
            cout << "Ora    : "; getline(cin, ora);
            try {
                auto &c = mc.cautaCursa(plecare, sosire, ora, data);
                cout << "\n--- CURSA GASITA ---\n";
                cout << "Plecare: " << c.getLocPlecare() << "  Sosire: " << c.getLocSosire()
                     << "  Data: " << c.getData() << "  Ora: " << c.getOraPlecare()
                     << "  Locuri: " << c.getLocuriDisponibile() << "\n";
            } catch (const NotFound &e) {
                cout << e.what() << endl;
            }
        }
        else if (opt == 3) {
            string plecare, sosire, ora, data;
            cout << "Plecare: "; getline(cin, plecare);
            cout << "Sosire : "; getline(cin, sosire);
            cout << "Data   : "; getline(cin, data);
            cout << "Ora    : "; getline(cin, ora);

            try {
                mc.rezervareLoc(plecare, sosire, ora, data);
                cout << "Rezervare efectuata.\n";
            } catch (const exception &e) {
                cout << "Eroare rezervare: " << e.what() << endl;
            }
        }
        else if (opt == 4) {
            cout << "\n--- BILETE ---\n";
            cout << "(funcționalitate bilete neimplementată în acest moment)\n";
        }
        else if (opt == 5) {
            cout << "Delogat.\n";
            return;
        }
        else {
            cout << "Optiune invalida.\n";
        }
    }
}

// ---------------- MENIU OPERATOR ----------------
void menuOperator(ManagerCurse &mc, GestionareCSV &gestion) {
    while (true) {
        cout << "\n===== MENIU OPERATOR =====\n";
        cout << "1. Adaugare cursa\n";
        cout << "2. Stergere cursa\n";
        cout << "3. Delogare\n";
        int opt = readInt("Alegere: ");

        if (opt == 1) {
            string ID, locPlecare, locSosire, data, ora;
            int loc;
            cout << "Introduceți detaliile cursei (Data: DD/MM/YYYY, Ora: HH:MM)\n";
            cout << "ID cursa: "; getline(cin, ID);
            cout << "Plecare : "; getline(cin, locPlecare);
            cout << "Sosire  : "; getline(cin, locSosire);
            cout << "Data    : "; getline(cin, data);
            cout << "Ora     : "; getline(cin, ora);
            loc = readInt("Locuri: ");

            try {
                mc.adaugaCursa(ID, locPlecare, locSosire, data, ora, loc);
                gestion.saveCurse("trips.csv", mc.curse);
                cout << "✔ Cursa adaugata cu succes\n";
            } catch (const exception &e) {
                cout << "Eroare la creare cursa: " << e.what() << "\n";
            }
        }
        else if (opt == 2) {
            string id;
            cout << "ID cursa de sters: ";
            getline(cin, id);

            try {
                mc.stergeCursa(id);
                gestion.saveCurse("trips.csv", mc.curse);
                cout << "✔ Cursa stearsa\n";
            } catch (const exception &e) {
                cout << "Eroare la stergere: " << e.what() << "\n";
            }

        }
        else if (opt == 3) {
            cout << "Delogare operator.\n";
            return;
        }
        else {
            cout << "Optiune invalida.\n";
        }
    }
}

// ---------------- MAIN APP ----------------
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
        cout << "\n===== MENIU PRINCIPAL =====\n";
        cout << "1. Login User\n";
        cout << "2. Adauga cont User\n";
        cout << "3. Login Operator\n";
        cout << "4. IESIRE\n";
        int opt = readInt("Alegere: ");

        if (opt == 1) {
            string email = citesteEmailValid("Email: ");
            string pass;
            cout << "Parola: ";
            getline(cin, pass);

            if (um.loginUser(email, pass)) {
                menuUser(um, mc, email);
            } else {
                cout << "✘ Login esuat\n";
            }
        }
        else if (opt == 2) {
            string nume, pren, email, pass;
            cout << "Nume: "; getline(cin, nume);
            cout << "Prenume: "; getline(cin, pren);
            email = citesteEmailValid("Email: ");
            cout << "Parola: "; getline(cin, pass);

            try {
                um.createUserAccount(nume, pren, email, pass);
            } catch (const exception &e) {
                cout << "Eroare: " << e.what() << endl;
            }
        }
        else if (opt == 3) {
            string email = citesteEmailValid("Email operator: ");
            string pass;
            cout << "Parola: ";
            getline(cin, pass);

            bool ok = false;
            for (auto &op : operators) {
                if (op.login(email, pass)) { ok = true; break; }
            }
            if (ok) {
                menuOperator(mc, gestion);
            } else {
                cout << "✘ Operator invalid\n";
            }
        }
        else if (opt == 4) {
            cout << "Program inchis.\n";
            break;
        }
        else {
            cout << "Optiune invalida.\n";
        }
    }

    return 0;
}
