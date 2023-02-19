#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <memory>
#include <thread>
#include <mutex>
#include <functional>

#include "./kdz/sorts.h"
#include "./kdz/utility.h"

using std::vector;

// чтобы изменить количество массивов для измерений каждой сортировки (усредненение), используйте переменные
// measurement_number_for_300 и measurement_number_for_4100

const uint64_t kMeasurementNumberFor300 = 250;
const uint64_t kMeasurementNumberFor4100 = 250;

// путь для таблиц сортировок
const std::string kSortTablesPath = "./kdz/sorts_tables/";

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    srand(time(nullptr));

    // количество сортировок
    const int sorts_count = 13;

    // указатели на сортировки
    vector<std::function<int(std::vector<int> &)>> sort_functions = {
            selectionSort, bubbleSort, firstIverson, secondIverson, insertionSort, binaryInsertionSort,
            countingSort, radixSort, mergeSort, quickSort, heapSort, ciuraShellSort,
            shellSort};

    // имена сортировок
    vector<std::string> sort_names = {"SelectionSort", "BubbleSort", "FirstIverson",
                                      "SecondIverson", "InsertionSort", "BinaryInsertionSort",
                                      "CountingSort", "RadixSort", "MergeSort",
                                      "QuickSort", "HeapSort", "ShellSortCiura",
                                      "ShellSort"};

    vector<std::string> sort_postfixes_arrays = {"", " sorted", " almost sorted", " reversed"};
    vector<std::string> sort_postfixes_values = {" values 0-5", " values 0-4000"};

    int count_300 = static_cast<int>(kMeasurementNumberFor300);
    int count_4100 = static_cast<int>(kMeasurementNumberFor4100);

    // эталонные массивы
    vector<vector<int>> benchmarks_50_to_300_values_5(count_300);
    vector<vector<int>> benchmarks_50_to_300_values_4000(count_300);
    vector<vector<int>> sorted_benchmarks_50_to_300_values_5(count_300);
    vector<vector<int>> sorted_benchmarks_50_to_300_values_4000(count_300);
    vector<vector<int>> almost_sorted_benchmarks_50_to_300_values_5(count_300);
    vector<vector<int>> almost_sorted_benchmarks_50_to_300_values_4000(count_300);
    vector<vector<int>> reversed_benchmarks_50_to_300_values_5(count_300);
    vector<vector<int>> reversed_benchmarks_50_to_300_values_4000(count_300);

    vector<vector<int>> benchmarks_100_to_4100_values_5(count_4100);
    vector<vector<int>> benchmarks_100_to_4100_values_4000(count_4100);
    vector<vector<int>> sorted_benchmarks_100_to_4100_values_5(count_4100);
    vector<vector<int>> sorted_benchmarks_100_to_4100_values_4000(count_4100);
    vector<vector<int>> almost_sorted_benchmarks_100_to_4100_values_5(count_4100);
    vector<vector<int>> almost_sorted_benchmarks_100_to_4100_values_4000(count_4100);
    vector<vector<int>> reversed_benchmarks_100_to_4100_values_5(count_4100);
    vector<vector<int>> reversed_benchmarks_100_to_4100_values_4000(count_4100);

    vector<int> bench_cycle = {count_300, count_4100};
    // чтобы не писать отдельную генерацию для размеров 300 и 4100, обернул её в один цикл. Так менее понятно, согласен
    for (int cycle = 0; cycle < 2; ++cycle) {
        vector<vector<int>> values_50_to_300 =
                (!cycle ? benchmarks_50_to_300_values_5 : benchmarks_50_to_300_values_4000);
        int n_300 = values_50_to_300.size();
        vector<vector<int>> sorted_values_50_to_300(n_300);
        vector<vector<int>> almost_sorted_values_50_to_300(n_300);
        vector<vector<int>> reversed_values_50_to_300(n_300);

        vector<vector<int>> values_100_to_4100 =
                (!cycle ? benchmarks_100_to_4100_values_5 : benchmarks_100_to_4100_values_4000);
        int n_4100 = values_100_to_4100.size();
        vector<vector<int>> sorted_values_100_to_4100(n_4100);
        vector<vector<int>> almost_sorted_values_100_to_4100(n_4100);
        vector<vector<int>> reversed_values_100_to_4100(n_4100);

        for (int i = 0; i < bench_cycle[cycle]; ++i) {
            vector<int> temp_300(300);
            vector<int> temp_4100(4100);

            // генерация значений для эталонных массивов
            generateRandom(temp_300, !cycle ? 6 : 4001);
            generateRandom(temp_4100, !cycle ? 6 : 4001);

            values_50_to_300[i] = temp_300;
            values_100_to_4100[i] = temp_4100;

            sorted_values_50_to_300[i] = temp_300;
            sorted_values_100_to_4100[i] = temp_4100;
            sortArray(sorted_values_50_to_300[i]);
            sortArray(sorted_values_100_to_4100[i]);

            reversed_values_50_to_300[i] = sorted_values_50_to_300[i];
            reversed_values_100_to_4100[i] = sorted_values_100_to_4100[i];
            reverseArray(reversed_values_50_to_300[i]);
            reverseArray(reversed_values_100_to_4100[i]);

            almost_sorted_values_50_to_300[i] = sorted_values_50_to_300[i];
            almost_sorted_values_100_to_4100[i] = sorted_values_100_to_4100[i];
            swapRandomElements(almost_sorted_values_50_to_300[i]);
            swapRandomElements(almost_sorted_values_100_to_4100[i]);
        }
        (!cycle ? benchmarks_50_to_300_values_5 : benchmarks_50_to_300_values_4000) =
                values_50_to_300;
        (!cycle ? benchmarks_100_to_4100_values_5 : benchmarks_100_to_4100_values_4000) =
                values_100_to_4100;

        (!cycle ? sorted_benchmarks_50_to_300_values_5 : sorted_benchmarks_50_to_300_values_4000) =
                sorted_values_50_to_300;
        (!cycle ? sorted_benchmarks_100_to_4100_values_5
                : sorted_benchmarks_100_to_4100_values_4000) = sorted_values_100_to_4100;

        (!cycle ? almost_sorted_benchmarks_50_to_300_values_5
                : almost_sorted_benchmarks_50_to_300_values_4000) = almost_sorted_values_50_to_300;
        (!cycle ? almost_sorted_benchmarks_100_to_4100_values_5
                : almost_sorted_benchmarks_100_to_4100_values_4000) =
                almost_sorted_values_100_to_4100;

        (!cycle ? reversed_benchmarks_50_to_300_values_5
                : reversed_benchmarks_50_to_300_values_4000) = reversed_values_50_to_300;
        (!cycle ? reversed_benchmarks_100_to_4100_values_5
                : reversed_benchmarks_100_to_4100_values_4000) = reversed_values_100_to_4100;
    }

    // объединение эталонных массивов в единый список для удобства
    vector<vector<vector<int>>> benchmarks_50_to_300 = {
            benchmarks_50_to_300_values_5,
            sorted_benchmarks_50_to_300_values_5,
            almost_sorted_benchmarks_50_to_300_values_5,
            reversed_benchmarks_50_to_300_values_5,
            benchmarks_50_to_300_values_4000,
            sorted_benchmarks_50_to_300_values_4000,
            almost_sorted_benchmarks_50_to_300_values_4000,
            reversed_benchmarks_50_to_300_values_4000};

    vector<vector<vector<int>>> benchmarks_100_to_4100 = {
            benchmarks_100_to_4100_values_5,
            sorted_benchmarks_100_to_4100_values_5,
            almost_sorted_benchmarks_100_to_4100_values_5,
            reversed_benchmarks_100_to_4100_values_5,
            benchmarks_100_to_4100_values_4000,
            sorted_benchmarks_100_to_4100_values_4000,
            almost_sorted_benchmarks_100_to_4100_values_4000,
            reversed_benchmarks_100_to_4100_values_4000};

    vector<vector<vector<vector<int>>>> benchmarks = {benchmarks_50_to_300, benchmarks_100_to_4100};

    // основной цикл выглядит как сортировка->тип массива(случайный/отсортированный/...)->размер массива(300/4100)->размер части массива(50/100/150/..)->усреднение

    for (int sort = 0; sort < sorts_count; ++sort) {
        // открытие файлов на запись (свой файл для каждой сортировки)
        vector<std::unique_ptr<std::ofstream>> tables_times;
        vector<std::unique_ptr<std::ofstream>> tables_operations;

        tables_times.emplace_back(
                new std::ofstream(kSortTablesPath + sort_names[sort] + "_time_small.csv",
                                  std::ofstream::out | std::ofstream::trunc));
        tables_times.emplace_back(
                new std::ofstream(kSortTablesPath + sort_names[sort] + "_time_big.csv",
                                  std::ofstream::out | std::ofstream::trunc));

        tables_operations.emplace_back(
                new std::ofstream(kSortTablesPath + sort_names[sort] + "_operations_small.csv",
                                  std::ofstream::out | std::ofstream::trunc));
        tables_operations.emplace_back(
                new std::ofstream(kSortTablesPath + sort_names[sort] + "_operations_big.csv",
                                  std::ofstream::out | std::ofstream::trunc));

        // вывод названий столбцов
        *tables_times[0] << "Sort";
        *tables_operations[0] << "Sort";
        for (int i = 50; i <= 300; i += 50) {
            *tables_times[0] << ';' << i;
            *tables_operations[0] << ';' << i;
        }
        *tables_times[0] << '\n';
        *tables_operations[0] << '\n';

        *tables_times[1] << "Sort";
        *tables_operations[1] << "Sort";
        for (int i = 100; i <= 4100; i += 100) {
            *tables_times[1] << ';' << i;
            *tables_operations[1] << ';' << i;
        }
        *tables_times[1] << '\n';
        *tables_operations[1] << '\n';

        // цикл типов массивов (случайный, отсортированный, почти, обратный) * 2 размера
        for (int array_type = 0; array_type < 8; ++array_type) {
            *tables_times[0] << sort_names[sort] + sort_postfixes_arrays[array_type % 4] +
                                sort_postfixes_values[array_type >= 4];
            *tables_times[1] << sort_names[sort] + sort_postfixes_arrays[array_type % 4] +
                                sort_postfixes_values[array_type >= 4];

            *tables_operations[0] << sort_names[sort] + sort_postfixes_arrays[array_type % 4] +
                                     sort_postfixes_values[array_type >= 4];
            *tables_operations[1] << sort_names[sort] + sort_postfixes_arrays[array_type % 4] +
                                     sort_postfixes_values[array_type >= 4];

            vector<int> start_size = {49, 99};
            vector<int> max_size = {300, 4100};
            vector<int> step = {50, 100};
            vector<int> measurement = {kMeasurementNumberFor300, kMeasurementNumberFor4100};

            vector<vector<uint64_t>> times_values = {vector<uint64_t>(6), vector<uint64_t>(41)};
            vector<vector<uint64_t>> operations_values = {vector<uint64_t>(6),
                                                          vector<uint64_t>(41)};
            vector<int> it = {0, 0};

            // цикл размера (300, 4100)
            for (int table = 0; table < 2; ++table) {
                for (int size = start_size[table]; size < max_size[table]; size += step[table]) {
                    uint64_t average_time = 0;
                    uint64_t average_operations = 0;

                    //цикл усреднения. Усреднение выполняется на разных массивах (но одинаковых для каждой сортировки)
                    for (uint64_t count = 0; count < static_cast<uint64_t>(measurement[table]);
                         ++count) {
                        // копирование части эталона
                        vector<int> to_sort =
                                vector<int>(benchmarks[table][array_type][count].begin(),
                                            benchmarks[table][array_type][count].begin() + size);

                        // замер времени
                        auto start = std::chrono::high_resolution_clock::now();

                        average_operations += sort_functions[sort](to_sort) / measurement[table];

                        auto elapsed = std::chrono::high_resolution_clock::now() - start;
                        uint64_t nanoseconds =
                                std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();

                        average_time += (nanoseconds / measurement[table]);
                    }

                    times_values[table][it[table]] = average_time;
                    operations_values[table][it[table]] = average_operations;
                    ++it[table];
                }

                // вывод результатов
                for (auto value: times_values[table]) {
                    *tables_times[table] << ';' << value;
                }
                for (auto value: operations_values[table]) {
                    *tables_operations[table] << ';' << value;
                }
                *tables_times[table] << '\n';
                *tables_operations[table] << '\n';
            }
        }
        for (int close = 0; close < static_cast<int>(tables_times.size()); ++close) {
            tables_times[close]->close();
            tables_operations[close]->close();
        }
        tables_times.clear();
        tables_operations.clear();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    return 0;
}
