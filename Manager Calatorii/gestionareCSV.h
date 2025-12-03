#ifndef GESTIONARECSV_H
#define GESTIONARECSV_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "user.h"
#include "cursa.h"
#include "operator.h"
#include "bilet.h"

class GestionareCSV{
  public:
  static std::vector<User> loadUsers(const std::string &filename);
  static void saveUsers(const std::string &filename, const std::vector<User> &users);

  static std::vector<Operator> loadOperators(const std::string &filename);
  static void saveOperators(const std::string &filename, const std::vector<Operator> &operators);

  static std::vector<Cursa> loadCurse(const std::string &filename);
  static void saveCurse(const std::string &filename, const std::vector<Cursa> &curse);

  std::vector<Bilet> loadBilete(const std::string &filename);
  void saveBilete(const std::string &filename, const std::vector<Bilet> &bilete);
};

#endif