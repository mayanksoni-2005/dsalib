#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <iostream>
#include <stdexcept>
#include<fstream>

namespace MayDSA {

template<typename T>
class Graph {
private:
    std::unordered_map<T, std::list<std::pair<T, int>>> adj;
    bool directed;

public:
    Graph(bool isDirected = false);

    void add_edge(const T& u, const T& v, int weight = 1);
    void remove_edge(const T& u, const T& v);
    void add_node(const T& u);
    void remove_node(const T& u);

    bool has_edge(const T& u, const T& v) const;
    std::vector<T> neighbors(const T& u) const;

    void print() const;

    bool dfs(const T& start, const T& target) const;
    bool bfs(const T& start, const T& target) const;
    std::vector<T> topological_sort() const;
    bool has_cycle() const;
    void export_dot(const std::string& filename) const; // for visulization
    void export_png(const std::string& png_filename) const;
};





template<typename T>
Graph<T>::Graph(bool isDirected) : directed(isDirected) {}

template<typename T>
void Graph<T>::add_node(const T& u) {
    if (adj.count(u) == 0) {
        adj[u] = {};
    }
}

template<typename T>
void Graph<T>::add_edge(const T& u, const T& v, int weight) {
    add_node(u);
    add_node(v);
    adj[u].push_back({v, weight});
    if (!directed) {
        adj[v].push_back({u, weight});
    }
}

template<typename T>
void Graph<T>::remove_edge(const T& u, const T& v) {
    if (adj.count(u)) {
        adj[u].remove_if([&](const std::pair<T, int>& p) { return p.first == v; });
    }
    if (!directed && adj.count(v)) {
        adj[v].remove_if([&](const std::pair<T, int>& p) { return p.first == u; });
    }
}

template<typename T>
bool Graph<T>::has_edge(const T& u, const T& v) const {
    if (adj.count(u)) {
        for (const auto& neighbor : adj.at(u)) {
            if (neighbor.first == v) return true;
        }
    }
    return false;
}

template<typename T>
std::vector<T> Graph<T>::neighbors(const T& u) const {
    std::vector<T> result;
    if (adj.count(u)) {
        for (const auto& [v, _] : adj.at(u)) {
            result.push_back(v);
        }
    }
    return result;
}

template<typename T>
void Graph<T>::print() const {
    for (const auto& [u, neighbors] : adj) {
        std::cout << u << " -> ";
        for (const auto& [v, weight] : neighbors) {
            std::cout << "(" << v << ", " << weight << ") ";
        }
        std::cout << "\n";
    }
}


template<typename T>
bool Graph<T>::dfs(const T& start, const T& target) const {
    std::unordered_map<T, bool> visited;
    std::function<bool(const T&)> dfs_helper = [&](const T& node) {
        if (node == target) return true;
        visited[node] = true;
        for (const auto& [neighbor, _] : adj.at(node)) {
            if (!visited[neighbor]) {
                if (dfs_helper(neighbor)) return true;
            }
        }
        return false;
    };

    if (!adj.count(start) || !adj.count(target)) return false;
    return dfs_helper(start);
}

template<typename T>
bool Graph<T>::bfs(const T& start, const T& target) const {
    if (!adj.count(start) || !adj.count(target)) return false;

    std::unordered_map<T, bool> visited;
    std::queue<T> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        T node = q.front(); q.pop();
        if (node == target) return true;

        for (const auto& [neighbor, _] : adj.at(node)) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return false;
}


template<typename T>
bool Graph<T>::has_cycle() const {
    std::unordered_map<T, bool> visited;
    std::function<bool(const T&, const T&)> dfs_cycle;

    if (directed) {
        std::unordered_map<T, int> state; // 0: unvisited, 1: visiting, 2: visited

        std::function<bool(const T&)> detect = [&](const T& node) {
            state[node] = 1;
            for (auto [nbr, _] : adj.at(node)) {
                if (state[nbr] == 1) return true; // back edge
                if (state[nbr] == 0 && detect(nbr)) return true;
            }
            state[node] = 2;
            return false;
        };

        for (const auto& [node, _] : adj) {
            if (state[node] == 0 && detect(node)) return true;
        }
        return false;
    } else {
        dfs_cycle = [&](const T& node, const T& parent) {
            visited[node] = true;
            for (auto [nbr, _] : adj.at(node)) {
                if (!visited[nbr]) {
                    if (dfs_cycle(nbr, node)) return true;
                } else if (nbr != parent) {
                    return true; // found cycle
                }
            }
            return false;
        };

        for (const auto& [node, _] : adj) {
            if (!visited[node] && dfs_cycle(node, node)) return true;
        }

        return false;
    }
}


template<typename T>
std::vector<T> Graph<T>::topological_sort() const {
    if (!directed) {
        throw std::logic_error("Topological sort only applies to directed graphs.");
    }

    std::unordered_map<T, bool> visited;
    std::vector<T> result;
    bool hasCycle = false;

    std::function<void(const T&)> dfs = [&](const T& node) {
        visited[node] = true;
        for (const auto& [nbr, _] : adj.at(node)) {
            if (!visited[nbr]) {
                dfs(nbr);
            }
        }
        result.push_back(node); // postorder
    };

    for (const auto& [node, _] : adj) {
        if (!visited[node]) {
            dfs(node);
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}

template<typename T>
void Graph<T>::export_dot(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string graph_type = directed ? "digraph" : "graph";
    std::string connector = directed ? " -> " : " -- ";

    file << graph_type << " G {\n";

    std::unordered_map<T, std::unordered_map<T, bool>> written;

    for (const auto& [u, neighbors] : adj) {
        if (neighbors.empty()) {
            file << "    \"" << u << "\";\n";
        }

        for (const auto& [v, weight] : neighbors) {
            if (!directed && written[v][u]) continue;
            file << "    \"" << u << "\"" << connector << "\"" << v << "\"";
            if (weight != 1)
                file << " [label=" << weight << "]";
            file << ";\n";
            written[u][v] = true;
        }
    }

    file << "}\n";
    file.close();
}

template<typename T>
void Graph<T>::export_png(const std::string& png_filename) const {
    const std::string dot_filename = "__temp_graph.dot";

    // Step 1: Write DOT file
    std::ofstream file(dot_filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open temp DOT file.");
    }

    std::string graph_type = directed ? "digraph" : "graph";
    std::string connector = directed ? " -> " : " -- ";

    file << graph_type << " G {\n";

    std::unordered_map<T, std::unordered_map<T, bool>> written;

    for (const auto& [u, neighbors] : adj) {
        if (neighbors.empty()) {
            file << "    \"" << u << "\";\n";
        }

        for (const auto& [v, weight] : neighbors) {
            if (!directed && written[v][u]) continue;
            file << "    \"" << u << "\"" << connector << "\"" << v << "\"";
            if (weight != 1)
                file << " [label=" << weight << "]";
            file << ";\n";
            written[u][v] = true;
        }
    }

    file << "}\n";
    file.close();

    // Step 2: Run Graphviz
    std::string command = "dot -Tpng " + dot_filename + " -o " + png_filename;
    int result = std::system(command.c_str());
    if (result != 0) {
        throw std::runtime_error("Graphviz 'dot' command failed.");
    }

    // Step 3: Delete temp DOT file
    std::remove(dot_filename.c_str());
}








} // namespace MayDSA