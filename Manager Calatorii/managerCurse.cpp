#include "managerCurse.h"
#include "exceptions.h"
#include <random>
#include <algorithm>
using namespace std;

static std::string toLower(const std::string &s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return r;
}

static std::string normalizeString(const std::string &s) {
    std::string res;
    for(char c : s){
        res += std::tolower(c);
    }
    return res;
}

static std::string normalizeDate(const std::string &date) {
    int zi = stoi(date.substr(0,2));
    int luna = stoi(date.substr(3,2));
    int an = stoi(date.substr(6,4));
    char buffer[11];
    sprintf(buffer, "%02d/%02d/%04d", zi, luna, an);
    std::string res(buffer);

    return res;
}

static std::string normalizeTime(const std::string &timeStr) {
    int ora = stoi(timeStr.substr(0,2));
    int min = stoi(timeStr.substr(3,2));
    char buffer[6];
    sprintf(buffer, "%02d:%02d", ora, min);
    std::string res(buffer);
    return res;
}


void ManagerCurse::adaugaCursa(const std::string ID, const std::string &locPlecare, const std::string &locSosire,
                    const std::string &dataPlecare, const std::string &oraPlecare, const int locuriDisponibile){

    Cursa cursa(ID, locPlecare, locSosire, dataPlecare, oraPlecare, locuriDisponibile);

    curse.push_back(cursa);
}
void ManagerCurse::stergeCursa(const std::string id) {
  for (auto it = curse.begin(); it != curse.end(); ++it) {
    if (it->getID() == id) {
      curse.erase(it);
      return;
    }
  }
  throw NotFound("Nu exista cursa cu ID-ul: " + id+"!");
}


//void afiseazaToatecursele();
Cursa& ManagerCurse::cautaCursa(const std::string &locPlecare, const std::string &locSosire,
                                const std::string &oraPlecare, const std::string &dataPlecare)
{
    std::string lp = normalizeString(locPlecare);
    std::string ls = normalizeString(locSosire);
    std::string op = normalizeTime(oraPlecare);
    std::string dp = normalizeDate(dataPlecare);

    for (auto &cursa : curse) {
        std::string c_lp = normalizeString(cursa.getLocPlecare());
        std::string c_ls = normalizeString(cursa.getLocSosire());
        std::string c_op = normalizeTime(cursa.getOraPlecare());
        std::string c_dp = normalizeDate(cursa.getData());

        if (c_lp == lp && c_ls == ls && c_op == op && c_dp == dp) {
            std::cout << "CURSA GASITA!"<<endl;
            return cursa;
        }
    }

    throw NotFound("Cursa nu a fost gasita!");
}




void ManagerCurse::rezervareLoc(const std::string &locPlecare, const std::string &locSosire,
                                const std::string &oraPlecare, const std::string &dataPlecare) {

    Cursa &cursa = cautaCursa(locPlecare, locSosire, oraPlecare, dataPlecare);

    if (cursa.locuriDisponibile > 0) {
        cursa.scadeLocuriDisponibile();
        cout << "Rezervare realizata cu succes!"<<endl;
    } else {
        throw NotFound("Nu mai sunt locuri disponibile la aceasta cursa!");
    }
}


