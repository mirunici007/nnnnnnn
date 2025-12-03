#include "bilet.h"

using namespace std;

Bilet::Bilet(const std::string &userID,
          const std::string &locPlecare,
          const std::string &locSosire,
          const std::string &dataPlecare,
          const std::string &oraPlecare)
          : userID(userID), locPlecare(locPlecare), locSosire(locSosire),
            dataPlecare(dataPlecare), oraPlecare(oraPlecare) {}

string Bilet::getUserID() const {
  return userID;
}
string Bilet::getLocPlecare() const {
  return locPlecare;
}
string Bilet::getLocSosire() const {
  return locSosire;
}
string Bilet::getDataPlecare() const {
  return dataPlecare;
}
string Bilet::getOraPlecare() const {
  return oraPlecare;
}

void Bilet::afisareDetaliiBilet()const{
  cout<<"Bilet: "<<endl;
  cout<<"Plecare: "<<locPlecare<<endl;
  cout<<"Sosire: "<<locSosire<<endl;
  cout<<"Data plecarii: "<<dataPlecare<<endl;
  cout<<"Ora plecarii: "<<oraPlecare<<endl;
}