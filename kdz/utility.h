#ifndef ILYA_CPP_UTILITY_H
#define ILYA_CPP_UTILITY_H

#include <vector>
#include <algorithm>
#include <ctime>
#include <functional>
#include <cstdlib>
#include <iostream>

void generateRandom(std::vector<int>& array, int max_value) {
    for (int i = 0; i < static_cast<int>(array.size()); ++i) {
        array[i] = rand() % max_value;
    }
}

void sortArray(std::vector<int>& array) {
    std::sort(array.begin(), array.end());
}

void reverseArray(std::vector<int>& array) {
    std::sort(array.begin(), array.end(), std::greater<int>());
}

bool isSorted(std::vector<int>& array) {
    std::vector<int> copy = array;
    std::sort(copy.begin(), copy.end());
    for (int i = 0; i < static_cast<int>(array.size()); ++i) {
        if (copy[i] != array[i]) {
            return false;
        }
    }
    return true;
}


bool isNotModified(std::vector<int> before, std::vector<int> after) {
    std::sort(before.begin(), before.end());
    std::sort(after.begin(), after.end());

    for (int i = 0; i < static_cast<int>(before.size()); ++i) {
        if (before[i] != after[i]) {
            return false;
        }
    }

    return true;
}

void printArray(std::vector<int>& array) {
    for (auto x : array) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

void swapRandomElements(std::vector<int>& array) {
    int n = (array.size() + 1) % 10;
    for (int i = 0; i < n; ++i) {
        int index1 = std::rand() % array.size();
        int index2 = std::rand() % array.size();
        std::swap(array[index1], array[index2]);
    }
}

#endif  // ILYA_CPP_UTILITY_H
