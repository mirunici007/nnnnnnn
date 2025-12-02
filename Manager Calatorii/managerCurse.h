#ifndef MANAGERCURSE_H
#define MANAGERCURSE_H

#include <iostream>
#include <string>
#include <vector>

#include "cursa.h"

class ManagerCurse{
    std::vector<Cursa> curse;
    bool isValidCity(const std::string &oras);
    bool isValidDate(const std::string &data);
  public:
    ManagerCurse()=default;
    ~ManagerCurse()=default;

    void adaugaCursa(const std::string &locPlecare, const std::string &locSosire,
                    const std::string &dataPlecare, const std::string &oraPlecare, const int locuriDisponibile);
    void stergeCursa(int index);

    //void afiseazaToatecursele();

    Cursa& cautaCursa(const std::string &locPlecare, const std::string &locSosire, const std::string &oraPlecare, const std::string &dataPlecare);
    void rezervareLoc(const std::string &locPlecare, const std::string &locSosire,
                                const std::string &oraPlecare, const std::string &dataPlecare);
};

#endif

