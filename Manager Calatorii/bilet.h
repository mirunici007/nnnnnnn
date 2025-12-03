#ifndef BILET_H
#define BILET_H

#include <iostream>
#include <string>

class Bilet {
    std::string userID;
    std::string locPlecare;
    std::string locSosire;
    std::string dataPlecare;
    std::string oraPlecare;

public:
    Bilet() = default;
    ~Bilet() = default;
    Bilet(const std::string &userID,
          const std::string &locPlecare,
          const std::string &locSosire,
          const std::string &dataPlecare,
          const std::string &oraPlecare);
    std::string getUserID() const;
    std::string getLocPlecare() const;
    std::string getLocSosire() const;
    std::string getDataPlecare() const;
    std::string getOraPlecare() const;

    void afisareDetaliiBilet()const;

};

#endif