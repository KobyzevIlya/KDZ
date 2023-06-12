#ifndef ILYA_CPP_UTILITY_H
#define ILYA_CPP_UTILITY_H

#include <iostream>
#include <vector>
#include <random>

typedef std::vector<std::vector<int>> Graph;

Graph generateCompleteGraph(int num_vertices, int seed) {
    Graph graph(num_vertices, std::vector<int>(num_vertices, 0));

    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> weight_generator(1, 10);

    for (int i = 0; i < num_vertices; ++i) {
        for (int j = i + 1; j < num_vertices; ++j) {
            int weight = weight_generator(gen);
            graph[i][j] = weight;
            graph[j][i] = weight;
        }
    }

    return graph;
}

Graph generateConnectedGraph(int num_vertices, double density, int seed) {
    Graph graph(num_vertices, std::vector<int>(num_vertices, 0));

    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> weight_generator(1, 10);
    std::uniform_real_distribution<double> probability_generator(0.0, 1.0);

    for (int i = 0; i < num_vertices; ++i) {
        for (int j = i + 1; j < num_vertices; ++j) {
            double probability = probability_generator(gen);
            if (probability <= density) {
                int weight = weight_generator(gen);
                graph[i][j] = weight;
                graph[j][i] = weight;
            }
        }
    }

    return graph;
}

Graph generateSparseGraph(int num_verticles, int seed) {
    Graph graph(num_verticles, std::vector<int>(num_verticles, 0));

    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> weight_generator(1, 10);

    for (int i = 1; i < num_verticles; ++i) {
        int weight = weight_generator(gen);
        int parent = i - 1;
        graph[parent][i] = weight;
        graph[i][parent] = weight;
    }

    return graph;
}

std::pair<int, int> getFirstNotZero(Graph& graph) {
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            if (graph[i][j] != 0) {
                return {i, j};
            }
        }
    }
    throw std::runtime_error("No verticles");
}

std::pair<int, int> getLastNotZero(const Graph& graph) {
    for (int i = graph.size() - 1; i >= 0; --i) {
        for (int j = graph.size() - 1; j >= 0; --j) {
            if (graph[i][j] != 0) {
                return {i, j};
            }
        }
    }
    throw std::runtime_error("No verticles");
}

int countVerticles(const Graph& graph) {
    return graph.size();
}

int countEdges(const Graph& graph) {
    int edges = 0;
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = i + 1; j < graph.size(); ++j) {
            if (graph[i][j] != 0) {
                ++edges;
            }
        }
    }
    return edges;
}

#endif  // ILYA_CPP_UTILITY_H
