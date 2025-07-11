#pragma once
#ifndef MAYDSA_HEAP_HPP
#define MAYDSA_HEAP_HPP

#include <vector>
#include <stdexcept>
#include <functional>
#include <iostream>

namespace MayDSA {

template<typename T, typename Compare = std::less<T>>
class Heap {
private:
    std::vector<T> data;
    Compare comp;

    void heapify_up(size_t idx) {
        while (idx > 0) {
            size_t parent = (idx - 1) / 2;
            if (comp(data[idx], data[parent])) {
                std::swap(data[idx], data[parent]);
                idx = parent;
            } else break;
        }
    }

    void heapify_down(size_t idx) {
        size_t size = data.size();
        while (true) {
            size_t left = 2 * idx + 1;
            size_t right = 2 * idx + 2;
            size_t best = idx;

            if (left < size && comp(data[left], data[best])) best = left;
            if (right < size && comp(data[right], data[best])) best = right;

            if (best == idx) break;

            std::swap(data[idx], data[best]);
            idx = best;
        }
    }

public:
    Heap() = default;

    void push(const T& val) {
        data.push_back(val);
        heapify_up(data.size() - 1);
    }

    void pop() {
        if (data.empty()) throw std::out_of_range("Heap is empty");
        std::swap(data[0], data.back());
        data.pop_back();
        if (!data.empty()) heapify_down(0);
    }

    const T& top() const {
        if (data.empty()) throw std::out_of_range("Heap is empty");
        return data[0];
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    void clear() {
        data.clear();
    }

    void print() const {
        std::cout << "[ ";
        for (const auto& x : data) std::cout << x << " ";
        std::cout << "]\n";
    }
};

using MinHeap = Heap<int, std::less<int>>;
using MaxHeap = Heap<int, std::greater<int>>;

} // namespace MayDSA

#endif // MAYDSA_HEAP_HPP