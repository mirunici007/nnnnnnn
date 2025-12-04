#include "managerCurse.h"
#include "exceptions.h"
#include <random>

using namespace std;

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
  throw NotFound("Nu exista cursa cu ID-ul: " + id);
}


//void afiseazaToatecursele();

Cursa& ManagerCurse::cautaCursa(const string &locPlecare, const string &locSosire,
                                const string &oraPlecare, const string &dataPlecare)
{
    for (auto &cursa : curse){
        if (cursa.locPlecare == locPlecare &&
            cursa.locSosire == locSosire &&
            cursa.oraPlecare == oraPlecare &&
            cursa.dataPlecare == dataPlecare){
            return cursa;
        }
    }
    throw NotFound("Cursa nu a fost găsită!");
}
void ManagerCurse::rezervareLoc(const std::string &locPlecare, const std::string &locSosire,
                                const std::string &oraPlecare, const std::string &dataPlecare){

  try{
    Cursa &cursa = cautaCursa(locPlecare, locSosire, oraPlecare, dataPlecare);

    if(cursa.locuriDisponibile>0){
      cursa.scadeLocuriDisponibile();
      cout<<"Rezervare realizata cu succes!"<<endl;
    }
    else{
      throw NotFound("Nu mai sunt locuri disponibile la aceasta cursa!");
    }
    }
  catch (const NotFound &e) {
    cout << e.what() << endl;
	}
}

