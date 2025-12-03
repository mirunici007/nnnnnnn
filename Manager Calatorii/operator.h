#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <vector>
#include "managerCurse.h"

class Operator{
  std::string email;
  std::string password;
  static std::vector<Operator> operators;

  public:
    Operator()=default;
    ~Operator()=default;
    Operator(std::string email, std::string password);

    std::string getEmail()const;
    std::string getPassword()const;

    bool login(const std::string &email, const std::string &password)const;
    void adaugaCursaManager(ManagerCurse &manager,
                             const std::string &locPlecare,
                             const std::string &locSosire,
                             const std::string &dataPlecare,
                             const std::string &oraPlecare,
                             int locuriDisponibile);
    void stergeCursaManager(ManagerCurse &manager, int index);
};

#endif