#include "cursa.h"

using namespace std;

Cursa::Cursa(const std::string ID, const std::string &locPlecare, const std::string &locSosire,const std::string &dataPlecare,
          const std::string &oraPlecare, const int locuriDisponibile):ID(ID), locPlecare(locPlecare), locSosire(locSosire),
                                                                           dataPlecare(dataPlecare) , oraPlecare(oraPlecare),
                                                                           locuriDisponibile(locuriDisponibile){}

string Cursa::getLocPlecare()const{
  return this->locPlecare;
}
string Cursa::getLocSosire()const{
  return this->locSosire;
}
string Cursa::getData() const{
  return this->dataPlecare;
}
string Cursa::getOraPlecare() const{
  return this->oraPlecare;
}
int Cursa::getLocuriDisponibile() const{
  return this->locuriDisponibile;
}
std::string Cursa::getID()const{
  return this->ID;
}


void Cursa::scadeLocuriDisponibile(){
  if(this->locuriDisponibile<0){
    throw NoSeatsAvailable("Nu mai sunt locuri disponibile!");
  }
  this->locuriDisponibile--;
}

void Cursa::afiseazaDetalii() const {
  std::cout << "ID: " << ID
            << " | " << locPlecare << " → " << locSosire
            << " | " << dataPlecare << " ora " << oraPlecare
            << " | Locuri ramase: " << locuriDisponibile
            << endl;
}