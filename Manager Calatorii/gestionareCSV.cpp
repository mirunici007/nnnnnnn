#include "gestionareCSV.h"
#include "managerCurse.h"

using namespace std;

static std::string normalizeString(const std::string &s) {
  std::string res;
  for(char c : s){
    res += std::tolower(c);
  }
  return res;
}

std::string normalizeDate(const std::string &date) {
  size_t first = date.find('/');
  size_t second = date.find('/', first + 1);

  int zi = stoi(date.substr(0, first));
  int luna = stoi(date.substr(first + 1, second - first - 1));
  int an = stoi(date.substr(second + 1));

  char buffer[11];
  sprintf(buffer, "%02d/%02d/%04d", zi, luna, an);
  return std::string(buffer);
}


static std::string normalizeTime(const std::string &timeStr) {
  int ora = stoi(timeStr.substr(0,2));
  int min = stoi(timeStr.substr(3,2));
  char buffer[6];
  sprintf(buffer, "%02d:%02d", ora, min);
  return std::string(buffer);
}

vector<User> GestionareCSV::loadUsers(const std::string &filename){
  vector<User> users;
  ifstream file(filename);
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
  if(!file.is_open()){
    throw InvalidData("Nu se poate deschide  fisierul " + filename);
  }

  file << "ID,Last,First,Email,Password\n";

  for (auto &user : users) {
    file << user.getID() << ","
         << user.getLastName() << ","
         << user.getFirstName() << ","
         << user.getEmail() << ","
         << user.getPassword() << endl;
  }
  file.flush();

  file.close();
}


vector<Operator> GestionareCSV::loadOperators(const std::string &filename){
  ifstream file;
  file.open(filename);
  if (!file.is_open()){
    throw InvalidData("Eroare la deschiderea fisierului  " + filename);
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
      throw InvalidData("Eroare la deschiderea fisierului " + filename);
    }

    for (auto &op: operators) {
      file << op.getEmail() << "," << op.getPassword() <<endl;
    }
}

vector<Cursa> GestionareCSV::loadCurse(const std::string &filename){
  ifstream file(filename);
  if (!file.is_open()) throw InvalidData("Eroare la citirea fisierului: " + filename);

  vector<Cursa> curse;
  string line;

  while (getline(file, line)) {
    stringstream ss(line);
    string ID, locPlecare, locSosire, dataPlecare, oraPlecare, locuriDisponibile;

    getline(ss, ID, ',');
    getline(ss, locPlecare, ',');
    getline(ss, locSosire, ',');
    getline(ss, dataPlecare, ',');
    getline(ss, oraPlecare, ',');
    getline(ss, locuriDisponibile, ',');

    int locuri = stoi(locuriDisponibile);

    curse.emplace_back(ID, normalizeString(locPlecare), normalizeString(locSosire),
                       normalizeDate(dataPlecare), normalizeTime(oraPlecare), locuri);
  }

  return curse;
}


void GestionareCSV::saveCurse(const std::string &filename, const std::vector<Cursa> &curse){
    ofstream file;
    file.open(filename);
    if (!file.is_open()){
      throw InvalidData("Eroare la deschiderea fisierului " + filename);
    }

    for (auto &c : curse) {
      file << c.getID() << ","
      	   << c.getLocPlecare() << ","
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
      throw InvalidData("Eroare la deschiderea fisierului " + filename);
    }

    for (auto &b : bilete) {
        file << b.getUserID() << ","
             << b.getLocPlecare() << ","
             << b.getLocSosire() << ","
             << b.getDataPlecare() << ","
             << b.getOraPlecare() <<endl;
    }
}

void GestionareCSV::appendBilet(const std::string &filename, const Bilet &bilet) {
  ofstream file(filename, ios::app);

  if (!file.is_open()) {
    throw InvalidData("Nu se poate deschide fisierul " + filename);
  }

  file << bilet.getUserID() << ","
       << bilet.getLocPlecare() << ","
       << bilet.getLocSosire() << ","
       << bilet.getDataPlecare() << ","
       << bilet.getOraPlecare() <<endl;

  file.close();
}
