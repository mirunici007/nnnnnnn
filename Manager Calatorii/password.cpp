#include "password.h"
#include <cstring>
#include <iostream>

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
    string result;

    for(char c: originalPassword){
        unsigned char enc = (c ^ key) + shift;

        char buffer[3];
        sprintf(buffer, "%02X", enc); // convertim în HEX
        result += buffer;
    }
    return result;
}


string Password::decryptCaesar(const string &encryptedPassword, char key, int shift){
    string result;

    for(size_t i=0; i<encryptedPassword.length(); i+=2){
        string hexByte = encryptedPassword.substr(i,2);
        unsigned char enc = stoi(hexByte,nullptr,16);

        char dec = (enc - shift) ^ key;
        result += dec;
    }
    return result;
}

bool Password::verifyPassword(const std::string &plainPassword, const std::string &encryptedPassword) {
    string encryptedInput = encryptCaesar(plainPassword, PASSWORD_KEY, PASSWORD_SHIFT);

    return encryptedInput == encryptedPassword;
}

