#pragma once
#ifndef MAYDSA_DSU_HPP
#define MAYDSA_DSU_HPP

#include <unordered_map>
#include <stdexcept>
#include <iostream>

namespace MayDSA {

template<typename T>
class DSU {
private:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, int> rank;

public:
    DSU() = default;

    // Create a new set with a single element
    void make_set(const T& x) {
        if (parent.count(x)) return;
        parent[x] = x;
        rank[x] = 0;
    }

    // Find the representative (with path compression)
    T find(const T& x) {
        if (!parent.count(x))
            throw std::runtime_error("Element not found in DSU");
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // Union two sets by rank
    void unite(const T& x, const T& y) {
        T root_x = find(x);
        T root_y = find(y);
        if (root_x == root_y) return;

        if (rank[root_x] < rank[root_y]) {
            parent[root_x] = root_y;
        } else if (rank[root_x] > rank[root_y]) {
            parent[root_y] = root_x;
        } else {
            parent[root_y] = root_x;
            rank[root_x]++;
        }
    }

    // Check if two elements are in the same set
    bool same_set(const T& x, const T& y) {
        return find(x) == find(y);
    }

    // Print representative of each element
    void print_sets() const {
        for (const auto& [x, _] : parent) {
            std::cout << x << " -> " << parent.at(x) << "\n";
        }
    }
};

} // namespace MayDSA

#endif // MAYDSA_DSU_HPP