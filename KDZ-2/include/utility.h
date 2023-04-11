#ifndef ILYA_CPP_UTILITY_H
#define ILYA_CPP_UTILITY_H

#include "search.h"
#include <iostream>

std::string generateRandomString(int alphabet_size, int lenght) {
    std::string result;

    for (int i = 0; i < lenght; ++i) {
        int digit = rand() % alphabet_size;
        result += digit + '0';
    }

    return result;
}

void insertWildcardCharacter(std::string& s, int num_wildcards) {
    for (int i = 0; i < num_wildcards; ++i) {
        int pos = rand() % (s.size() + 1);
        s[pos] = kWildcardCharacter;
    }
}

#endif  // ILYA_CPP_UTILITY_H
