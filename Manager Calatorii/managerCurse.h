#ifndef MANAGERCURSE_H
#define MANAGERCURSE_H

#include <iostream>
#include <string>
#include <vector>

#include "cursa.h"

class ManagerCurse{

    bool isValidCity(const std::string &oras);
    bool isValidDate(const std::string &data);
  public:
    ManagerCurse()=default;
    ~ManagerCurse()=default;

    std::vector<Cursa> curse;

    void adaugaCursa(const std::string ID, const std::string &locPlecare, const std::string &locSosire,
                    const std::string &dataPlecare, const std::string &oraPlecare, const int locuriDisponibile);
    void stergeCursa(const std::string id);

    //void afiseazaToatecursele();

    Cursa& cautaCursa(const std::string &locPlecare, const std::string &locSosire, const std::string &oraPlecare, const std::string &dataPlecare);
    void rezervareLoc(const std::string &locPlecare, const std::string &locSosire,
                                const std::string &oraPlecare, const std::string &dataPlecare);

    //bool loginUser(const std::string &email, const std::string &password);
};

#endif

