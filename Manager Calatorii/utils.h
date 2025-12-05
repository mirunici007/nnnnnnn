//
// Created by HP-15S on 12/5/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

class Utils {
public:
    static bool emailValid(const std::string &email);
    static std::string citesteEmailValid(const std::string &prompt);

    static int readInt(const std::string &prompt);

    template<typename Func>
    static std::string citesteValid(const std::string &prompt, Func validator) {
        std::string input;
        while (true) {
            std::cout << prompt;
            getline(std::cin, input);
            try {
                validator(input);
                return input;
            } catch (const std::exception &e) {
                std::cout << "Eroare: " << e.what() << " Reincercati.\n";
            }
        }
    }

    static void validateCity(const std::string &city);
    static void validateDate(const std::string &date);
    static void validateTime(const std::string &timeStr);

    static std::string normalizeString(const std::string &s);
    static std::string normalizeDate(const std::string &date);
    static std::string normalizeTime(const std::string &timeStr);
};



#endif //UTILS_H
