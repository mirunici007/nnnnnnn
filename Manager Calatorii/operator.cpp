#include "operator.h"

using namespace std;

bool Operator::login(const string &emailInput, const string &passwordInput) const {

    if(email != emailInput)
        return false;

    return Password::verifyPassword(passwordInput, password);
}


void Operator::setPassword(const std::string &newPassword) {
    password = Password::encryptCaesar(newPassword, PASSWORD_KEY, PASSWORD_SHIFT); // criptăm la salvare
}


Operator::Operator(string email, string password): email(email), password(password){}

string Operator::getEmail()const{
  return email;
}
string Operator::getPassword()const{
  return password;
}

/*void Operator::adaugaCursaManager(ManagerCurse &manager,
                         const std::string &locPlecare,
                         const std::string &locSosire,
                         const std::string &dataPlecare,
                         const std::string &oraPlecare,
                         int locuriDisponibile);*/
void Operator::stergeCursaManager(ManagerCurse &manager, const std::string &id) {
    try {
        manager.stergeCursa(id);
        cout << "Cursa stearsa cu succes!" << endl;
    } catch (const NotFound &e) {
        throw OperatorActionFailed("Stergerea cursei a eșuat!");
    }
}
