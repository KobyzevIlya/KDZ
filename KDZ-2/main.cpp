#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
#include <memory>
#include <fstream>

#include "./include/utility.h"
#include "./include/search.h"

const uint64_t kMeasurementNumber = 100;

const std::string kTablesPath = "./tables/";

signed main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    srand(time(nullptr));

    std::vector<std::function<int(const std::string&, const std::string&)>> search_functions = {naiveSearch, simpleKmpSearch, avancedKmpSearch};
    std::vector<std::string> search_names = {"NaiveSearch", "SimpleKmpSearch", "AdvancedKmpSearch"};
    std::vector<std::string> search_postfixes = {"clear_small_time", "clear_big_time", "mod_small_time", "mod_big_time"};
    std::vector<std::string> alphabet_postfixes = {"_binary", "_quaternary"};
    std::vector<std::string> type_postfixes = {"", "_1_wildcards", "_2_wildcards", "_3_wildcards", "_4_wildcards"};

    std::vector<std::unique_ptr<std::ofstream>> tables;
    std::vector<std::string> binary_benchmarks = {generateRandomString(2, 10000), generateRandomString(2, 100000)};
    std::vector<std::string> quaternary_benchmarks = {generateRandomString(4, 10000), generateRandomString(4, 100000)};
    std::vector<std::vector<std::string>> benchmarks = {binary_benchmarks, quaternary_benchmarks};

    for (int table = 0; table < 4; ++table) {
        tables.emplace_back(new std::ofstream(kTablesPath + search_postfixes[table] + ".csv", std::ofstream::out | std::ofstream::trunc));

        *tables[table] << "Search";
        for (int size = 100; size <= 3000; size += 100) {
            *tables[table] << ';' << size;
        }
        *tables[table] << '\n';
        for (int search = 0; search < static_cast<int>(search_functions.size()); ++search) {
            for (int alphabet = 0; alphabet < 2; ++alphabet) {
                for (int type = 0; type < 5; ++type) {
                    if ((table < 2 && type > 0) || (table >= 2 && (type == 0))) {
                        continue;
                    }
                    *tables[table] << search_names[search] << alphabet_postfixes[alphabet] << type_postfixes[type];

                    for (int size = 100; size <= 3000; size += 100) {
                        int position = rand() % ((table % 2 ? 100000 : 10000) - size);
                        std::string pattern = benchmarks[alphabet][table % 2].substr(position, size);
                        insertWildcardCharacter(pattern, type);

                        uint64_t average_time = 0;
                        for (int count = 0; count < static_cast<int>(kMeasurementNumber); ++count) {
                            auto start = std::chrono::high_resolution_clock::now();

                            search_functions[search](pattern, benchmarks[alphabet][table % 2]);

                            auto elapsed = std::chrono::high_resolution_clock::now() - start;

                            uint64_t nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
                            average_time += (nanoseconds / kMeasurementNumber);
                        }
                        *tables[table] << ';' << average_time;
                    }
                    *tables[table] << '\n';
                }
            }
        }
        tables[table]->close();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    std::cout << "Time taken: " << duration.count() << " seconds" << '\n';

    return 0;
}
