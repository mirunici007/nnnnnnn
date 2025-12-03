#include "gestionareCSV.h"

using namespace std;

vector<User> GestionareCSV::loadUsers(const std::string &filename){
  vector<User> users;

  ifstream file;
  file.open(filename);
  if (!file.is_open()){
    throw InvalidData("Eroare la deschiderea fisierului pentru citire: " + filename);
  }

  string line;
  while (getline(file, line)) {
    stringstream ss(line);
    string id, last, first, email, password;

    getline(ss, id, ',');
    getline(ss, last, ',');
    getline(ss, first, ',');
    getline(ss, email, ',');
    getline(ss, password, ',');

    if (!id.empty())
      users.emplace_back(id, last, first, email, password);
  }

  return users;
}
void GestionareCSV::saveUsers(const std::string &filename, const std::vector<User> &users){
  ofstream file(filename);
  for (auto &user : users) {
    file << user.getID() << ","
         << user.getLastName() << ","
         << user.getFirstName() << ","
         << user.getEmail() << ","
         << user.getPassword() << endl;
  }
}

vector<Operator> GestionareCSV::loadOperators(const std::string &filename){
  ifstream file;
  file.open(filename);
  if (!file.is_open()){
    throw InvalidData("Eroare la deschiderea fisierului pentru citire: " + filename);
  }

  vector<Operator> operators;
  string line;

  while (getline(file, line)) {
    stringstream ss(line);
    string email, password;
    getline(ss, email, ',');
    getline(ss, password, ',');

    if (!email.empty()){
      operators.emplace_back(email, password);
      }
  }

    return operators;
}

void GestionareCSV::saveOperators(const std::string &filename, const std::vector<Operator> &operators){
    ofstream file;
    file.open(filename);
    if (!file.is_open()){
      throw InvalidData("Eroare la deschiderea fisierului pentru citire: " + filename);
    }

    for (auto &op: operators) {
      file << op.getEmail() << "," << op.getPassword() <<endl;
    }
}

vector<Cursa> GestionareCSV::loadCurse(const std::string &filename){
    ifstream file;
    file.open(filename);
    if (!file.is_open()){
      throw InvalidData("Eroare la deschiderea fisierului pentru citire: " + filename);
    }

    vector<Cursa> curse;
    string line;

    while (getline(file, line)) {
      stringstream ss(line);
      string locPlecare, locSosire, dataPlecare, oraPlecare, locuriDisponibile;

      getline(ss, locPlecare, ',');
      getline(ss, locSosire, ',');
      getline(ss, dataPlecare, ',');
      getline(ss, oraPlecare, ',');
      getline(ss, locuriDisponibile, ',');

      int locuri = stoi(locuriDisponibile);

      curse.emplace_back(locPlecare, locSosire, dataPlecare, oraPlecare, locuri);
    }

    return curse;
}

void GestionareCSV::saveCurse(const std::string &filename, const std::vector<Cursa> &curse){
    ofstream file;
    file.open(filename);
    if (!file.is_open()){
      throw InvalidData("Eroare la deschiderea fisierului pentru citire: " + filename);
    }

    for (auto &c : curse) {
      file << c.getLocPlecare() << ","
           << c.getLocSosire() << ","
           << c.getData() << ","
           << c.getOraPlecare() << ","
           << c.getLocuriDisponibile() <<endl;
    }
}

vector<Bilet> GestionareCSV::loadBilete(const string &filename) {
    vector<Bilet> bilete;
    ifstream file;
    file.open(filename);

    if (!file.is_open()){
      throw InvalidData("Eroare la deschiderea fisierului pentru citire: " + filename);
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        string userID, locPlecare, locSosire, dataPlecare, oraPlecare;
        stringstream ss(line);

        getline(ss, userID, ',');
        getline(ss, locPlecare, ',');
        getline(ss, locSosire, ',');
        getline(ss, dataPlecare, ',');
        getline(ss, oraPlecare, ',');

        bilete.emplace_back(userID, locPlecare, locSosire, dataPlecare, oraPlecare);
    }

    return bilete;
}

void GestionareCSV::saveBilete(const string &filename, const vector<Bilet> &bilete) {
    ofstream file(filename);

    if (!file.is_open()){
      throw InvalidData("Eroare la deschiderea fisierului pentru citire: " + filename);
    }

    for (auto &b : bilete) {
        file << b.getUserID() << ","
             << b.getLocPlecare() << ","
             << b.getLocSosire() << ","
             << b.getDataPlecare() << ","
             << b.getOraPlecare() <<endl;
    }
}
