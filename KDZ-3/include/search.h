#ifndef ILYA_CPP_SEARCH_H
#define ILYA_CPP_SEARCH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>

#include "utility.h"

int dijkstra(const Graph& graph, int start, int end) {
    int n = graph.size();

    std::vector<int> distances(n, std::numeric_limits<int>::max());
    distances[start] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, start)); // Добавляем начальную вершину в очередь с приоритетами

    while (!pq.empty()) {
        int u = pq.top().second; // Извлекаем вершину с минимальным расстоянием
        pq.pop();

        // Обходим соседей вершины u
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] != 0) { // Проверяем наличие ребра между вершинами u и v
                int weight = graph[u][v];
                int distance_through_u = distances[u] + weight;

                if (distance_through_u < distances[v]) { // Если найден более короткий путь
                    distances[v] = distance_through_u;
                    pq.push(std::make_pair(distances[v], v));
                }
            }
        }
    }

    return distances[end];
}

int floydWarshall(const Graph& graph, int start, int end) {
    // Создаем матрицу расстояний и инициализируем ее
    std::vector<std::vector<int>> distances(graph);
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            if (i == j)
                distances[i][j] = 0;
            else if (distances[i][j] == 0)
                distances[i][j] = std::numeric_limits<int>::max();
        }
    }

    // Выполняем алгоритм Флойда-Уоршелла
    for (int k = 0; k < graph.size(); ++k) {
        for (int i = 0; i < graph.size(); ++i) {
            for (int j = 0; j < graph.size(); ++j) {
                if (distances[i][k] != std::numeric_limits<int>::max() &&
                    distances[k][j] != std::numeric_limits<int>::max() &&
                    distances[i][k] + distances[k][j] < distances[i][j]) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
            }
        }
    }

    return distances[start][end];
}

int bellmanFord(const Graph& graph, int start, int end) {
    int n = graph.size();
    std::vector<int> distances(n, std::numeric_limits<int>::max());
    distances[start] = 0;

    // Релаксация ребер n - 1 раз
    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (graph[u][v] != 0) { // Проверяем наличие ребра между вершинами u и v
                    int weight = graph[u][v];
                    if (distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                        distances[v] = distances[u] + weight;
                    }
                }
            }
        }
    }

    return distances[end];
}

struct Node {
    int vertex;      // Вершина
    int f_score;      // Оценка f(x) = g(x) + h(x)
    int g_score;      // Расстояние от начальной вершины до текущей вершины

    Node(int v, int f, int g) : vertex(v), f_score(f), g_score(g) {}
};

struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.f_score > b.f_score;
    }
};

int aStar(const Graph& graph, int start, int end) {
    int num_vertices = graph.size();
    std::vector<int> h_scores(num_vertices, std::numeric_limits<int>::max());  // Оценки h(x) от каждой вершины до целевой вершины
    std::priority_queue<Node, std::vector<Node>, Compare> open_set;  // Открытое множество вершин для обработки

    h_scores[end] = 0;  // Оценка h(x) для целевой вершины

    open_set.push(Node(start, h_scores[start], 0));

    std::vector<int> g_scores(num_vertices, std::numeric_limits<int>::max());  // Расстояния от начальной вершины до каждой вершины
    g_scores[start] = 0;

    while (!open_set.empty()) {
        Node current = open_set.top();
        open_set.pop();

        if (current.vertex == end) {
            // Достигнута целевая вершина
            return g_scores[current.vertex];
        }

        for (int neighbor = 0; neighbor < num_vertices; ++neighbor) {
            if (graph[current.vertex][neighbor] != 0) {  // Проверяем наличие ребра между текущей вершиной и соседней вершиной
                int tentativeg_score = g_scores[current.vertex] + graph[current.vertex][neighbor];

                if (tentativeg_score < g_scores[neighbor]) {
                    // Обновляем путь к соседней вершине
                    g_scores[neighbor] = tentativeg_score;
                    int f_score = g_scores[neighbor] + h_scores[neighbor];
                    open_set.push(Node(neighbor, f_score, g_scores[neighbor]));
                }
            }
        }
    }

    // Целевая вершина недостижима
    return -1;
}

#endif  // ILYA_CPP_SEARCH_H
