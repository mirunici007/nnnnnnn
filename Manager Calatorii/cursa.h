#ifndef CURSA_H
#define CURSA_H

#include <iostream>
#include "exceptions.h"

class Cursa{
    std::string locPlecare;
    std::string locSosire;
    std::string dataPlecare;
    std::string oraPlecare;
    int locuriDisponibile;

    public:

    friend class ManagerCurse;

    Cursa()=default;
    Cursa(const std::string &locPlecare, const std::string &locSosire,const std::string &dataPlecare,
          const std::string &oraPlecare, const int locuriDisponibile);
    ~Cursa()=default;
    std::string getLocPlecare() const;
    std::string getLocSosire()const;
    std::string getData() const;
    std::string getOraPlecare() const;
    int getLocuriDisponibile() const;

    void scadeLocuriDisponibile();
};


#endif