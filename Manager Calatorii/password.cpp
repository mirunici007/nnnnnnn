#include "password.h"

using namespace std;

Password::Strength Password::checkPasswordStrength(const string &password){
    bool hasUpper=false;
    bool hasLower=false;
    bool hasDigit=false;
    bool hasSpecialChar=false;

    char specialChars[] = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/`~\\";

    for(char c: password){
        if(isupper(c)){
            hasUpper=true;
        }
        if(islower(c)){
            hasLower=true;
        }
        if(isdigit(c)){
            hasDigit=true;
        }
        if(strchr(specialChars, c)){
            hasSpecialChar=true;
        }
    }

    if(password.length() < 6 || !(hasUpper || hasLower || hasDigit || hasSpecialChar))
        return WEAK;
    if(password.length() < 10 || !(hasUpper && hasLower && hasDigit && hasSpecialChar))
        return OK;
    return GOOD;
}

string Password::encryptCaesar(const string &originalPassword, char key, int shift){
    string result = originalPassword;

    for(char &c: result){
        c = (c ^ key) + shift;
    }
    return result;
}

string Password::decryptCaesar(const string &encryptedPassword, char key, int shift){
    string result = encryptedPassword;

    for(char &c: result){
        c = (c - shift) ^ key;
    }
    return result;
}

