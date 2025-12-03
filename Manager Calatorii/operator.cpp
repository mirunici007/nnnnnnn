#include "operator.h"

using namespace std;

bool Operator::login(const string &email, const string &password)const{
    for(const auto &user: operators){
        if(user.getEmail() == email && user.getPassword()==password){
            cout<<"Login reusit! Bine ai venit!"<<endl;
            return true;
        }
    }
    throw InvalidLogin("Email sau parola incorecta!");
    return false;
}

Operator::Operator(string email, string password): email(email), password(password){}

string Operator::getEmail()const{
  return email;
}
string Operator::getPassword()const{
  return password;
}

void adaugaCursaManager(ManagerCurse &manager,
                         const std::string &locPlecare,
                         const std::string &locSosire,
                         const std::string &dataPlecare,
                         const std::string &oraPlecare,
                         int locuriDisponibile);
void stergeCursaManager(ManagerCurse &manager, int index){
    try {
        manager.stergeCursa(index);
        cout<<"Cursa stearsa cu succes!"<<endl;
    } catch (const NotFound &e) {
        throw OperatorActionFailed("Stergerea cursei a eșuat: " + std::string(e.what()));
    }
}