#ifndef ILYA_CPP_SEARCH_H
#define ILYA_CPP_SEARCH_H

#include <iostream>

const char kWildcardCharacter = '?';

int naiveSearch(const std::string& what, const std::string& where) {
    int what_length = what.size();
    int where_length = where.size();
    int count = 0;

    for (int i = 0; i <= where_length - what_length; ++i) {
        bool yes_its_here = true;
        for (int j = 0; j < what_length; ++j) {
            if (what[j] != kWildcardCharacter && what[j] != where[i + j]) {
                yes_its_here = false;
                break;
            }
        }
        if (yes_its_here) {
            ++count;
        }
    }

    return count;
}

std::vector<int> makeBr(const std::string& s) {
    int n = s.size();
    std::vector<int> br(n);
    for (int i = 1; i < n; ++i) {
        int j = br[i - 1];

        while (j > 0 && (s[i] != s[j] && s[j] != kWildcardCharacter)) {
            j = br[j - 1];
        }

        if (s[i] == s[j] || s[j] == kWildcardCharacter) {
            ++j;
        }

        br[i] = j;
    }

    return br;
}

int simpleKmpSearch(const std::string& what, const std::string& where) {
    int m = what.size();
    int n = where.size();
    std::vector<int> br = makeBr(what);
    int count = 0;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && (j == m || (what[j] != where[i] && what[j] != kWildcardCharacter))) {
            j = br[j - 1];
        }

        if (what[j] == where[i] || what[j] == kWildcardCharacter) {
            ++j;
        }

        if (j == m) {
            ++count;
            j = br[j - 1];
        }
    }

    return count;
}

std::vector<int> makeBrs(const std::string& s) {
    std::vector<int> br = makeBr(s);
    int n = br.size();
    std::vector<int> brs(n);
    brs[0] = 0;
    brs[n - 1] = br[n - 1];
    for (int i = 1; i < n - 1; ++i) {
        if (s[br[i]] != s[i + 1] && s[br[i]] != kWildcardCharacter) {
            brs[i] = br[i];
        } else {
            brs[i] = brs[br[i]];
        }
    }
    return brs;
}

int avancedKmpSearch(const std::string& what, const std::string& where) {
    int m = what.size();
    int n = where.size();
    std::vector<int> brs = makeBrs(what);
    int count = 0;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && (j == m || (what[j] != where[i] && what[j] != kWildcardCharacter))) {
            j = brs[j - 1];
        }

        if (what[j] == where[i] || what[j] == kWildcardCharacter) {
            ++j;
        }

        if (j == m) {
            ++count;
            j = brs[j - 1];
        }
    }

    return count;
}

#endif  // ILYA_CPP_SEARCH_H
