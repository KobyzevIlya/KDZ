#ifndef ILYA_CPP_SORTS_H
#define ILYA_CPP_SORTS_H

#include <vector>
#include <algorithm>

// сортировки, сгенерированные chatGPT

// На каждой итерации находим минимальный элемент в оставшейся части массива и меняем его местами с первым неотсортированным элементом. Таким образом,
// на каждой итерации сортируется по одному элементу, пока не будут отсортированы все элементы.

int selectionSort(std::vector<int>& array) {
    int n = array.size();
    int num_operations = 0;
    for (int i = 0; i < n - 1; ++i) {
        ++num_operations; // сравнение i
        int min_index = i;
        ++num_operations; //объявление переменной
        for (int j = i + 1; j < n; ++j) {
            ++num_operations; // увеличиваем количество операций при каждом сравнении
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


int bubbleSort(std::vector<int>& array) {
    int n = array.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
            }
        }
    }
    return 0;
}

// Функция сортирует массив в порядке возрастания путем сравнения пар соседних элементов и перестановки их местами, если они находятся в
// неправильном порядке. Если внутренний цикл не производит никаких перестановок, то это означает, что массив уже отсортирован, и внешний цикл может
// быть прерван.
//
// Условие Айверсона 1 означает, что если в процессе сортировки не было ни одной перестановки элементов, то массив уже отсортирован и дополнительные
// итерации не требуются. Это помогает сократить время выполнения алгоритма в тех случаях, когда массив уже близок к отсортированному состоянию.

int firstIverson(std::vector<int>& array) {
    int n = array.size();
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;  // если не было перестановок, то массив уже отсортирован
        }
    }
    return 0;
}

// В этой оптимизации запоминается позиция последнего обмена на предыдущей итерации внешнего цикла. Эта позиция - верхняя грацица просмотра массива на
// следующей итерации. Если позиция == 0, то обменов не было и алгоритм завершает работу. Оптимизация позволяет уменьшить количесво проходов
// внутреннего цикла

int secondIverson(std::vector<int>& array) {
    int n = array.size();
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;  // если не было перестановок, то массив уже отсортирован
        }
    }
    return 0;
}


// Внешний цикл проходится по элементам массива, начиная со второго элемента. В каждой итерации внешнего цикла текущий элемент массива, находящийся на
// позиции i, сравнивается с элементами, находящимися перед ним (начиная с элемента на позиции i - 1) и с помощью внутреннего цикла вставляется на
// свою правильную позицию в отсортированную часть массива

int insertionSort(std::vector<int>& array) {
    int n = array.size();
    for (int i = 1; i < n; ++i) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
    return 0;
}

int binaryInsertionSort(std::vector<int>& array) {
    int n = array.size();
    for (int i = 1; i < n; ++i) {
        int x = array[i];
        int left = 0;
        int right = i - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (array[mid] > x) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        for (int j = i - 1; j >= left; j--) {
            array[j + 1] = array[j];
        }
        array[left] = x;
    }
    return 0;
}

int countingSort(std::vector<int>& vec) {
    // find min and max elements
    int min = *std::min_element(vec.begin(), vec.end());
    int max = *std::max_element(vec.begin(), vec.end());

    // create count vector
    std::vector<int> count(max - min + 1, 0);
    for (int x : vec) {
        count[x - min]++;
    }

    // transform count vector
    for (int i = 1; i < static_cast<int>(count.size()); i++) {
        count[i] += count[i - 1];
    }

    // create result vector
    std::vector<int> result(vec.size());
    for (int i = vec.size() - 1; i >= 0; i--) {
        int x = vec[i];
        int pos = count[x - min] - 1;
        result[pos] = x;
        count[x - min]--;
    }

    // copy result to vec
    vec = result;

    return 0;
}

int radixSort(std::vector<int>& array) {
    int n = array.size();
    for (int digit = 0; digit < 4; ++digit) {
        std::vector<int> numbers(256, 0);
        std::vector<int> sorted_values(n);

        // устойчивая сортировка подсчетом
        for (int i = 0; i < n; ++i) {
            ++numbers[(static_cast<unsigned>(array[i]) >> 8 * digit) & 255];
        }
        for (int i = 1; i < 256; ++i) {
            numbers[i] += numbers[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            sorted_values[--numbers[(static_cast<unsigned>(array[i]) >> 8 * digit) & 255]] = array[i];
        }

        array = sorted_values;
    }
    return 0;
}

void merge(std::vector<int>& array, int begin, int middle, int end) {
    std::vector<int> buffer(end - begin);
    int j_begin = begin, j_end = middle;

    for (int i = 0; i < end - begin; ++i) {
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

    int n = end - begin;
    int left = begin;
    for (int i = 0; i < n; ++i) {
        array[left] = buffer[i];
        ++left;
    }
}

void mergeSortHelper(std::vector<int>& array, int begin, int end) {
    if (end - begin <= 1) {
        return;
    }

    int middle = begin + ((end - begin) / 2);

    mergeSortHelper(array, begin, middle);
    mergeSortHelper(array, middle, end);

    merge(array, begin, middle, end);
}

// mergeSort разделяет входной массив пополам и рекурсивно вызывает себя на обеих половинах. Когда размер подмассива достигает единицы, вызывается
// функция merge, которая объединяет два отсортированных подмассива в один отсортированный массив.

int mergeSort(std::vector<int>& array) {
    mergeSortHelper(array, 0, array.size());
    return 0;
}

void quickSortHelper(std::vector<int>& array, int left, int right) {
    if (left >= right) {
        return;
    }
    int pivot = array[left];
    int i = left + 1;
    int j = right;
    while (i <= j) {
        while (i <= j && array[i] <= pivot) {
            ++i;
        }
        while (i <= j && array[j] >= pivot) {
            j--;
        }
        if (i < j) {
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[left], array[j]);
    quickSortHelper(array, left, j - 1);
    quickSortHelper(array, j + 1, right);
}

// В качестве опорного используется первый элемент. Он сравнивается с другими, затем массив делится на 2 части: элементы слева от опорного элемента,
// которые меньше его значения, и элементы справа от опорного элемента, которые больше его значения. Затем quicksort рекурсивно вызывается для каждой
// половины массива.

int quickSort(std::vector<int>& array) {
    quickSortHelper(array, 0, array.size() - 1);
    return 0;
}

void heapify(std::vector<int>& array, int n, int i) {
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    int largest = i;

    if (left < n && array[left] > array[largest]) {
        largest = left;
    }
    if (right < n && array[right] > array[largest]) {
        largest = right;
    }
    if (largest != i) {
        std::swap(array[i], array[largest]);
        heapify(array, n, largest);
    }
}

void buildHeap(std::vector<int>& array) {
    int n = array.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(array, n, i);
    }
}

// Пирамидальная сортировка

int heapSort(std::vector<int>& array) {
    buildHeap(array);
    int n = array.size();
    for (int i = n - 1; i >= 0; --i) {
        std::swap(array[0], array[i]);
        heapify(array, i, 0);
    }
    return 0;
}

// Последовательность Циура

int ciuraShellSort(std::vector<int>& array) {
    int n = array.size();
    // Определяем последовательность Циура
    int gap = 1;
    while (gap < n) {
        gap = 3 * gap + 1;
    }
    // Начинаем сортировку
    while (gap > 0) {
        for (int i = gap; i < n; ++i) {
            int temp = array[i];
            int j = i;
            while (j >= gap && array[j - gap] > temp) {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = temp;
        }
        gap /= 3;
    }
    return 0;
}

// Сортировка Шелла

int shellSort(std::vector<int>& array) {
    int n = array.size();
    // Выбираем размер шага начиная с половины размера массива и далее уменьшаем его вдвое на каждой итерации.
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Перебираем элементы, начиная с gap-го элемента, и сравниваем каждый элемент с предыдущим элементом на шаге gap.
        for (int i = gap; i < n; i += 1) {
            int temp = array[i];
            // Сравниваем элементы на шаге gap и меняем их местами, если они не в правильном порядке.
            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
    return 0;
}

#endif  // ILYA_CPP_SORTS_H
