#include "utils.h"
#include <iostream>
#include <regex>
#include <ctime>
#include <limits>
#include <cctype>
#include <algorithm>
using namespace std;

bool Utils::emailValid(const string &email) {
    size_t at = email.find('@');
    size_t dot = email.find('.', at + 1);
    return at != string::npos &&
           dot != string::npos &&
           at > 0 &&
           dot < email.size() - 1;
}

string Utils::citesteEmailValid(const string &prompt) {
    string email;

    while (true) {
        cout << prompt;
        getline(cin, email);

        if (emailValid(email))
            return email;

        cout << "Eroare: Email invalid! Format corect: ceva@domeniu.com\n";
        cout << "Introduceti din nou emailul!\n";
    }
}

int Utils::readInt(const string &prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        } else {
            cout << "Eroare: input invalid. Introduceti un numar.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Utils::validateCity(const string &city) {
    if (city.empty()) throw invalid_argument("Orasul nu poate fi gol");
    for (char c : city) {
        if (!isalpha(c) && c != ' ') throw invalid_argument("Orasul trebuie sa contina doar litere");
    }
}

void Utils::validateDate(const string &date) {
    regex re(R"((0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\d{4})");
    if (!regex_match(date, re)) throw invalid_argument("Format data invalid (DD/MM/YYYY)");

    int zi = stoi(date.substr(0,2));
    int luna = stoi(date.substr(3,2));
    int an = stoi(date.substr(6,4));

    time_t t = time(nullptr);
    tm* now = localtime(&t);

    if (an < now->tm_year + 1900 ||
        (an == now->tm_year + 1900 && luna < now->tm_mon + 1) ||
        (an == now->tm_year + 1900 && luna == now->tm_mon + 1 && zi < now->tm_mday))
        throw invalid_argument("Data nu poate fi in trecut");
}

void Utils::validateTime(const string &timeStr) {
    regex re(R"(([01][0-9]|2[0-3]):([0-5][0-9]))");
    if (!regex_match(timeStr, re)) throw invalid_argument("Format ora invalid (HH:MM)");
}

string Utils::normalizeString(const string &s) {
    string res;
    for(char c : s){
        switch(c){
            case 'ă': case 'Ă': res += 'a'; break;
            case 'î': case 'Î': res += 'i'; break;
            case 'â': case 'Â': res += 'a'; break;
            case 'ș': case 'Ș': res += 's'; break;
            case 'ț': case 'Ț': res += 't'; break;
            default: res += tolower(c); break;
        }
    }
    return res;
}

string Utils::normalizeDate(const string &date) {
    int zi = stoi(date.substr(0,2));
    int luna = stoi(date.substr(3,2));
    int an = stoi(date.substr(6,4));
    char buffer[11];
    sprintf(buffer, "%02d/%02d/%04d", zi, luna, an);
    return string(buffer);
}

string Utils::normalizeTime(const string &timeStr) {
    int ora = stoi(timeStr.substr(0,2));
    int min = stoi(timeStr.substr(3,2));
    char buffer[6];
    sprintf(buffer, "%02d:%02d", ora, min);
    return string(buffer);
}
