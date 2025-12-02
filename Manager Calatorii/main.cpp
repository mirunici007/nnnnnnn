//srand(time(0));
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <ctime>

#include "password.h" // existent in repo

using namespace std;

// helper: convert Password::Strength to string
string strengthToString(Password::Strength s) {
    switch (s) {
        case Password::WEAK:   return "WEAK";
        case Password::OK: return "OK";
        case Password::GOOD: return "GOOD";
        default: return "UNKNOWN";
    }
}

// Simple CSV reader that skips header and returns rows as vector<string>
vector<vector<string>> readCsv(const string &path) {
    vector<vector<string>> rows;
    ifstream f(path);
    if (!f.is_open()) return rows;
    string line;
    // skip header if present
    if (!getline(f, line)) return rows;
    while (getline(f, line)) {
        vector<string> cols;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            cols.push_back(cell);
        }
        rows.push_back(cols);
    }
    f.close();
    return rows;
}

bool fileExists(const string &path) {
    ifstream f(path);
    return f.good();
}

void appendLine(const string &path, const string &line) {
    ofstream f(path, ios::app);
    if (!f.is_open()) throw runtime_error("Nu pot deschide fisierul pentru scriere: " + path);
    f << line << '\n';
    f.close();
}

bool validEmail(const string &email) {
    auto at = email.find('@');
    if (at == string::npos) return false;
    auto dot = email.find('.', at);
    if (dot == string::npos) return false;
    return dot > at + 1 && at > 0;
}

int main() {
    cout << "=== Test harness pentru gestionare-calatorii ===\n\n";

    // 1) Test password strength + encrypt/decrypt
    vector<string> samples = {
        "abc",
        "Abc123",
        "Abc123!",
        "Very$trongPass123"
    };

    cout << "Test password strength si criptare/decriptare:\n";
    char key = 'K';
    int shift = 3;
    for (auto &p : samples) {
        auto s = Password::checkPasswordStrength(p);
        cout << "  parola: \"" << p << "\" -> strength: " << strengthToString(s) << '\n';
        string enc = Password::encryptCaesar(p, key, shift);
        string dec = Password::decryptCaesar(enc, key, shift);
        cout << "    encrypted: " << enc << "\n";
        cout << "    decrypted: " << dec << (dec == p ? " (ok)" : " (mismatch)") << "\n";
    }
    cout << "\n";

    // 2) Operator login test (operators.csv format: username,encrypted_password)
    const string opsFile = "operators.csv";
    if (fileExists(opsFile)) {
        cout << "--- Operator login test (operators.csv gasit) ---\n";
        auto rows = readCsv(opsFile);
        cout << "Introdu username operator pentru test: ";
        string uname; getline(cin, uname);
        cout << "Introdu parola: ";
        string upass; getline(cin, upass);

        bool found = false;
        for (auto &r : rows) {
            if (r.size() >= 2 && r[0] == uname) {
                found = true;
                string stored = r[1];
                string enc = Password::encryptCaesar(upass, key, shift);
                if (enc == stored) cout << "Operator autentificat cu succes.\n";
                else cout << "Autentificare operator esuata: parola incorecta.\n";
                break;
            }
        }
        if (!found) cout << "Operator inexistent in operators.csv\n";
    } else {
        cout << "Fisierul operators.csv nu exista; sar testul operator login.\n";
    }
    cout << "\n";

    // 3) Creare utilizator (users.csv: email,encrypted_password,fullname)
    const string usersFile = "users.csv";
    cout << "--- Test creare utilizator ---\n";
    cout << "Email (sau ENTER pentru a sari): ";
    string email; getline(cin, email);
    if (!email.empty()) {
        try {
            if (!validEmail(email)) throw runtime_error("Format email invalid.");
            cout << "Parola: ";
            string pass1; getline(cin, pass1);
            cout << "Repeta parola: ";
            string pass2; getline(cin, pass2);
            if (pass1 != pass2) throw runtime_error("Parolele nu coincid.");

            auto strength = Password::checkPasswordStrength(pass1);
            if (strength == Password::WEAK) {
                throw runtime_error("Parola too weak. Nu poate fi salvata.");
            }
            string enc = Password::encryptCaesar(pass1, key, shift);
            string fullname = "Nume Prenume"; // demo
            // if file absent, add header
            if (!fileExists(usersFile)) {
                appendLine(usersFile, "email,encrypted_password,fullname");
            }
            appendLine(usersFile, email + "," + enc + "," + fullname);
            cout << "Utilizator salvat in users.csv (email: " << email << ")\n";
        } catch (const exception &e) {
            cerr << "Eroare la creare utilizator: " << e.what() << "\n";
        }
    } else {
        cout << "Sarit creare utilizator.\n";
    }
    cout << "\n";

    // 4) Listare curse (trips.csv: id,from,to,date,time,seats,price)
    const string tripsFile = "trips.csv";
    if (fileExists(tripsFile)) {
        cout << "--- Curse disponibile (trips.csv) ---\n";
        auto trips = readCsv(tripsFile);
        for (auto &t : trips) {
            // defensive checks
            if (t.size() >= 7) {
                cout << "ID=" << t[0] << " " << t[1] << "->" << t[2] << " " << t[3] << " " << t[4]
                     << " seats:" << t[5] << " price:" << t[6] << "\n";
            }
        }

        // rezervare demo
        cout << "\nIntrodu id cursa pentru rezervare (ENTER pentru a sari): ";
        string id; getline(cin, id);
        if (!id.empty()) {
            bool found = false;
            for (auto &t : trips) if (!t.empty() && t[0] == id) { found = true; break; }
            if (!found) {
                cout << "Cursa inexistenta cu id=" << id << "\n";
            } else {
                cout << "Introdu ora rezervarii (HH:MM): ";
                string hour; getline(cin, hour);
                if (hour.size() != 5 || hour[2] != ':' || !isdigit(hour[0])) {
                    cout << "Format ora invalid.\n";
                } else {
                    // append reservations.csv: reservation_id,trip_id,user_email,reserved_at_hour,created_at
                    const string resFile = "reservations.csv";
                    if (!fileExists(resFile)) appendLine(resFile, "reservation_id,trip_id,user_email,reserved_at_hour,created_at");
                    // create simple id
                    static int nextId = 1000;
                    time_t now = time(nullptr);
                    char buf[64];
                    strftime(buf, sizeof(buf), "%FT%T", localtime(&now));
                    // use email from earlier creation if present, otherwise placeholder
                    string userEmail = email.empty() ? "demo@example.com" : email;
                    string line = to_string(nextId++) + "," + id + "," + userEmail + "," + hour + "," + string(buf);
                    appendLine(resFile, line);
                    cout << "Rezervare adaugata: " << line << "\n";
                }
            }
        } else {
            cout << "Sarit rezervare.\n";
        }
    } else {
        cout << "Nu exista trips.csv; sar listare curse.\n";
    }

    cout << "\n=== Sfarsit test ===\n";
    return 0;
}