#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
#include <fstream>
#include <memory>

#include "./include/utility.h"
#include "./include/search.h"

const std::string kTablesPath = "./tables/";
const uint64_t kMeasurementNumber = 1;

signed main() {    
    auto start_time = std::chrono::high_resolution_clock::now();

    int seed = 42;
    
    std::vector<std::function<int(const Graph& graph, int start, int end)>> search_functions = {dijkstra, floydWarshall, bellmanFord, aStar};
    std::vector<std::string> search_names = {"Dijkstra", "FloydWarshall", "BellmanFord", "AStar"};
    std::vector<std::string> search_postfixes = {"_time", "_verticles", "_edges"};
    std::vector<std::string> graph_postfixes = {"_complete", "_connected", "_sparse"};

    std::vector<Graph> completeGraphs;
    std::vector<Graph> connectedGraphs;
    std::vector<Graph> sparseGraphs;

    for (int num_verticles = 10; num_verticles <= 1010; num_verticles += 50) {
        completeGraphs.push_back(generateCompleteGraph(num_verticles, seed));
        connectedGraphs.push_back(generateConnectedGraph(num_verticles, 0.4, seed));
        sparseGraphs.push_back(generateSparseGraph(num_verticles, seed));
    }

    std::vector<std::vector<Graph>> benchmarks = {completeGraphs, connectedGraphs, sparseGraphs};

    std::vector<std::unique_ptr<std::ofstream>> tables;
    
    for (int table = 0; table < 3; ++table) {
        tables.emplace_back(new std::ofstream(kTablesPath + search_postfixes[table] + ".csv", std::ofstream::out | std::ofstream::trunc));

        *tables[table] << "Search";
        for (int size = 10; size <= 1010; size += 50) {
            *tables[table] << ';' << size;
        }
        *tables[table] << '\n';
    }

    for (int search = 0; search < search_names.size(); ++search) {
        for (int type = 0; type < 3; ++type) {
            *tables[0] << search_names[search] << graph_postfixes[type] << search_postfixes[0];
            *tables[1] << search_names[search] << graph_postfixes[type] << search_postfixes[1];
            *tables[2] << search_names[search] << graph_postfixes[type] << search_postfixes[2];

            std::cout << search_names[search] << graph_postfixes[type] << search_postfixes[0] << '\n'; //debug

            for (int size = 0; size < benchmarks[type].size(); ++size) {
                Graph graph = benchmarks[type][size];
                int start = getFirstNotZero(graph).first;
                int end = getLastNotZero(graph).first;
                
                uint64_t average_time = 0;
                for (int count = 0; count < static_cast<int>(kMeasurementNumber); ++count) {
                    auto start_time = std::chrono::high_resolution_clock::now();

                    int ans = search_functions[search](graph, start, end); // debug

                    auto elapsed_time = std::chrono::high_resolution_clock::now() - start_time;

                    uint64_t nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_time).count();
                    average_time += (nanoseconds / kMeasurementNumber);
                }
                std::cout << size << '\n'; //debug
                *tables[0] << ';' << average_time;
                *tables[1] << ';' << countVerticles(graph);
                *tables[2] << ';' << countEdges(graph);
            }
            *tables[0] << '\n';
            *tables[1] << '\n';
            *tables[2] << '\n';
        }
    }

    tables[0]->close();
    tables[1]->close();
    tables[2]->close();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    std::cout << "Time taken: " << duration.count() << " seconds" << '\n';

    return 0;
}