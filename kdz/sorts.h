#ifndef ILYA_CPP_SORTS_H
#define ILYA_CPP_SORTS_H

#include <vector>
#include <algorithm>

// сортировки, сгенерированные chatGPT

int selectionSort(std::vector<int> &array) {
    int n = array.size();
    int num_operations = 0;
    for (int i = 0; i < n - 1; ++i) {
        int min_index = i;
        num_operations += 3; // сравнение i, инремент i и объявление переменной
        for (int j = i + 1; j < n; ++j) {
            num_operations += 3; // увеличиваем количество операций при каждом сравнении (в цикле и в array) + инкремент
            if (array[j] < array[min_index]) {
                min_index = j;
                ++num_operations; // присваивание
            }
        }
        ++num_operations; // сравнение min_index
        if (min_index != i) {
            std::swap(array[i], array[min_index]);
            num_operations += 3; // считаем swap за 3 операции
        }
    }
    return num_operations;
}

int bubbleSort(std::vector<int> &array) {
    int n = array.size();
    int num_operations = 0;
    for (int i = n - 1; i >= 1; --i) {
        num_operations += 2; // сравнение i + инкремент
        for (int j = 0; j < i; ++j) {
            num_operations += 4; // сравнение j, вычисление  - i - 1, сравнение array, инкремент j
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                num_operations += 3; // swap считаем за 3 операции
            }
        }
    }
    return num_operations;
}

int firstIverson(std::vector<int> &array) {
    int size = array.size();
    int i = 0;
    bool t = true;
    int num_operations = 2; // объявление 2 переменных
    while (t == true) {
        t = false;
        num_operations += 2;
        for (int j = 0; j < size - i - 1; ++j) {
            num_operations += 3; // цикл + сравнение
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                t = true;
                num_operations += 4; //swap считаем за 3 операции
            }
        }
        ++i;
        ++num_operations;
    }
    return num_operations;
}

int secondIverson(std::vector<int> &array) {
    int size = array.size();
    int i = 0;
    int last_pos = size - i - 1;
    int new_pos;
    int num_operations = 4; //объявление 2 переменных, 2 вычитания
    while (last_pos != 0) {
        new_pos = -1;
        num_operations += 2; //цикл, присваивание
        for (int j = 0; j < last_pos; ++j) {
            num_operations += 3; //цикл, сравнение
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                new_pos = j;
                num_operations += 4;
            }
        }
        num_operations += 2; //сравнение, присваивание
        if (new_pos== -1) {
            last_pos = 0;
        } else {
            last_pos = new_pos;
        }
        ++i;
        ++num_operations;
    }
    return num_operations;
}


int insertionSort(std::vector<int> &array) {
    int n = array.size();
    int num_operations = 0;
    for (int i = 1; i < n; ++i) {
        int key = array[i];
        int j = i - 1;
        num_operations += 6; // присваивание key, j, сравнение i в цикле, два сравнения в while, инкремент
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            --j;
            num_operations += 2; // присваивание array, декремент j
        }
        array[j + 1] = key;
        num_operations += 1; // присваивание array
    }
    return num_operations;
}

int binaryInsertionSort(std::vector<int> &array) {
    int n = array.size();
    int num_operations = 0;
    for (int i = 1; i < n; ++i) {
        int x = array[i];
        int left = 0;
        int right = i - 1;
        num_operations += 6; // присваивание x, left, right, вычитание, сравнение i, инкремент
        while (left <= right) {
            int mid = left + (right - left) / 2;
            num_operations += 4; // присваивание, сложение, вычитание, деление, сравнение left и right
            if (array[mid] > x) {
                right = mid - 1;
                num_operations += 2; // присваивание right, сравнение array
            } else {
                left = mid + 1;
                num_operations += 2; // присваивание left, сравнение array
            }
        }
        for (int j = i - 1; j >= left; --j) {
            array[j + 1] = array[j];
            num_operations += 3; // присваивание array, сравнение j в цикле, декремент
        }
        array[left] = x;
        ++num_operations; // присваивание array
    }
    return num_operations;
}

int countingSort(std::vector<int> &array) {
    int min = *std::min_element(array.begin(), array.end());
    int max = *std::max_element(array.begin(), array.end());

    int num_operations = array.size() * 2; // для нахождения максимального и минимального элемента надо провести size сравнений

    num_operations += max - min + 1; // объявление вектора
    std::vector<int> count(max - min + 1, 0);
    for (int x: array) {
        count[x - min]++;
        num_operations += 2; // проход по массиву и инкремент
    }

    for (int i = 1; i < static_cast<int>(count.size()); ++i) {
        num_operations += 4; // сравнения i и сложение с присваиванием, инкремент
        count[i] += count[i - 1];
    }

    std::vector<int> result(array.size());
    num_operations += array.size(); // копирование всех элементов
    for (int i = array.size() - 1; i >= 0; --i) {
        int x = array[i];
        int pos = count[x - min] - 1;
        result[pos] = x;
        count[x - min]--;
        num_operations += 6; //цикл, вычитание, 3 присваивания, декремент, декремент i
    }

    array = result;
    num_operations += array.size(); // копирование всех элементов

    return num_operations;
}

int radixSort(std::vector<int> &array) {
    int n = array.size();
    int num_operations = 0;
    for (int digit = 0; digit < 8; ++digit) {
        num_operations += 2 + 16 + n; // цикл + объявление 2 векторов
        std::vector<int> numbers(16, 0); // 16 вместо 256
        std::vector<int> sorted_values(n);

        for (int i = 0; i < n; ++i) {
            num_operations += 2 + 4; // цикл, инкремент, сдвиг, умножение, побитовое и
            ++numbers[(static_cast<unsigned>(array[i]) >> 4 * digit) & 15]; 
        }
        for (int i = 1; i < 16; ++i) {
            num_operations += 4; // цикл, сложение, присваивание
            numbers[i] += numbers[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            num_operations += 2 + 5; // цикл, инкремент, сдвиг, умножение, побитовое и, присваивание
            sorted_values[--numbers[(static_cast<unsigned>(array[i]) >> 4 * digit) & 15]] = array[i];
        }

        array = sorted_values;
        num_operations += n; // копирование всех элементов
    }
    return num_operations;
}

void merge(std::vector<int> &array, int begin, int middle, int end, int& num_operations) {
    num_operations += end - begin + 3; // объявление вектора, два присваивания, вычитание
    std::vector<int> buffer(end - begin);
    int j_begin = begin, j_end = middle;

    for (int i = 0; i < end - begin; ++i) {
        ++num_operations;
        num_operations += 4; //сравнение и инкремент, присваивание, инкремент (каждую итерацию только один блок if/else)
        if (j_end == end) {
            buffer[i] = array[j_begin];
            ++j_begin;
        } else if (j_begin == middle) {
            buffer[i] = array[j_end];
            ++j_end;
        } else if (array[j_begin] <= array[j_end]) {
            buffer[i] = array[j_begin];
            ++j_begin;
        } else {
            buffer[i] = array[j_end];
            ++j_end;
        }
    }

    num_operations += 3; // присваивание, вычитание, присваивание
    int n = end - begin;
    int left = begin;
    for (int i = 0; i < n; ++i) {
        num_operations += 4; // цикл, присваивание, инкремент
        array[left] = buffer[i];
        ++left;
    }
}

void mergeSortHelper(std::vector<int> &array, int begin, int end, int& num_operations) {
    num_operations += 2; // сложение, присваивание
    if (end - begin <= 1) {
        return;
    }

    int middle = begin + ((end - begin) / 2);
    num_operations += 4; // присваивание, сложение, вычитание, деление

    num_operations += 2; // два вызова функций
    mergeSortHelper(array, begin, middle, num_operations);
    mergeSortHelper(array, middle, end, num_operations);

    merge(array, begin, middle, end, num_operations);
}

int mergeSort(std::vector<int> &array) {
    int num_operations = 0;
    mergeSortHelper(array, 0, array.size(), num_operations);

    return num_operations;
}

void quickSortHelper(std::vector<int> &array, int left, int right, int& num_operations) {
    ++num_operations; // сравнение
    if (left >= right) {
        return;
    }
    num_operations += 3; // 3 присваивания, сложение
    int pivot = array[left];
    int i = left + 1;
    int j = right;
    while (i <= j) {
        ++num_operations; // итерация цикла
        while (i <= j && array[i] <= pivot) {
            ++i;
            num_operations += 3; // два сравнения, инкремент
        }
        while (i <= j && array[j] >= pivot) {
            --j;
            num_operations += 2; // два сравнения, декремент
        }
        if (i < j) {
            std::swap(array[i], array[j]);
            num_operations += 4; // сравнение, swap
        }
    }
    std::swap(array[left], array[j]);
    num_operations += 3; // swap считаем за 3 элемента
    quickSortHelper(array, left, j - 1, num_operations);
    quickSortHelper(array, j + 1, right, num_operations);
}

int quickSort(std::vector<int> &array) {
    int num_operations = 0;
    quickSortHelper(array, 0, array.size() - 1, num_operations);
    return num_operations;
}

void heapify(std::vector<int> &array, int n, int i, int& num_operations) {
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    int largest = i;

    num_operations += 3 + 2 + 2; // 3 присваивания, два сложения, два умножения

    if (left < n && array[left] > array[largest]) {
        largest = left;
        num_operations += 3; // 2 сравния, присваивание
    }
    if (right < n && array[right] > array[largest]) {
        largest = right;
        num_operations += 3; // 2 сравния, присваивание
    }
    if (largest != i) {
        std::swap(array[i], array[largest]);
        num_operations += 4; // сравнение, swap
        heapify(array, n, largest, num_operations);
    }
}

void buildHeap(std::vector<int> &array, int& num_operations) {
    int n = array.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        num_operations += 2; // цикл
        heapify(array, n, i, num_operations);
    }
}

// Пирамидальная сортировка

int heapSort(std::vector<int> &array) {
    int num_operations = 0;
    buildHeap(array, num_operations);
    int n = array.size();
    for (int i = n - 1; i >= 0; --i) {
        std::swap(array[0], array[i]);
        num_operations += 5; // swap + цикл
        heapify(array, i, 0, num_operations);
    }
    return num_operations;
}

int ciuraShellSort(std::vector<int> &array) {
    int n = array.size();
    int num_operations = 9; // присваивание
    int gaps[] = {1750, 701, 301, 132, 57, 23, 10, 4, 1};
    int num_gaps = 9;
    for (int g = 0; g < num_gaps; ++g) {
        int gap = gaps[g];
        num_operations += 2; // присваивание, чтение из массива
        for (int i = gap; i < n; ++i) {
            num_operations += 4; // цикл, два присваивания
            int temp = array[i];
            int j = i;
            while (j >= gap && array[j - gap] > temp) {
                num_operations += 2; //цикл
                array[j] = array[j - gap];
                j -= gap;
                num_operations += 4; // два присваивания, два вычитания
            }
            array[j] = temp;
            ++num_operations; // присваивание
        }
    }
    return num_operations;
}


int shellSort(std::vector<int> &array) {
    int n = array.size();
    int num_operations = 0;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        num_operations += 2; // цикл
        for (int i = gap; i < n; i += 1) {
            num_operations += 4; // цикл, два присваивания
            int temp = array[i];
            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                num_operations += 4; // два сравнения, присваивание с вычитанием
                array[j] = array[j - gap];
                num_operations += 2; // присваивание, вычитание
            }
            array[j] = temp;
            ++num_operations; // присваивание
        }
    }
    return num_operations;
}

#endif  // ILYA_CPP_SORTS_H
