#ifndef DSALIB_VECTOR_HPP
#define DSALIB_VECTOR_HPP

#include <iostream>
#include <stdexcept>
#include <algorithm>

/**
 * @brief A simple dynamic array implementation similar to std::vector.
 * 
 * @tparam T Type of the elements stored in the Vector.
 */
// WE ARE DEFINING VECTOR CLASS BELOW
namespace MayDSA{

template<typename T>
class Vector {
private:
    T* data;          // Pointer to the actual array
    size_t length;    // Number of elements stored
    size_t capacity;  // Allocated memory

    // I am implementing 2* strategy for capacity
    void resize() {
        capacity = capacity == 0 ? 1 : capacity * 2;
        T* new_data = new T[capacity];
        for (size_t i = 0; i < length; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }

public:
    // Constructor
    Vector() : data(nullptr), length(0), capacity(0) {}

    // Destructor
    ~Vector() {
        delete[] data;
    }

    // Copy constructor
    Vector(const Vector<T>& other) : data(new T[other.capacity]), length(other.length), capacity(other.capacity) {
        for (size_t i = 0; i < length; ++i){
            data[i] = other.data[i];
        }
    }

    // Move constructor
    Vector(Vector<T>&& other) noexcept : data(other.data), length(other.length), capacity(other.capacity) {
        other.data = nullptr;
        other.length = 0;
        other.capacity = 0;
    }

    // Access operator
    T& operator[](size_t index) {
        if (index >= length) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    // Const version
    const T& operator[](size_t index) const {
        if (index >= length) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    // Add element to end
    void push_back(const T& value) {
        if (length == capacity) resize();
        data[length++] = value;
    }

    // Remove last element
    void pop_back() {
        if (length == 0) throw std::underflow_error("Vector is empty");
        length--;
    }

    // Insert at position
    void insert(size_t index, const T& value) {
        if (index > length) throw std::out_of_range("Index out of bounds");
        if (length == capacity) resize();
        for (size_t i = length; i > index; i--){
            data[i] = data[i - 1];
        }
        data[index] = value;
        length++;
    }

    // Remove at position
    void remove(size_t index) {
        if (index >= length) throw std::out_of_range("Index out of bounds");
        for (size_t i = index; i < length - 1; ++i){
            data[i] = data[i + 1];
        }
        length--;
    }

    // Reverse the array
    void reverse() {
        for (size_t i = 0; i < length / 2; ++i)
            std::swap(data[i], data[length - 1 - i]);
    }

    // Return size
    size_t size() const {
        return length;
    }

    // Clear all elements
    void clear() {
        length = 0;
    }

    // Find first index of value, or -1
    int find(const T& value) const {
        for (size_t i = 0; i < length; ++i)
            if (data[i] == value)
                return i;
        return -1;
    }

    // Print vector
    void print() const {
        std::cout << "[ ";
        for (size_t i = 0; i < length; ++i)
            std::cout << data[i] << " ";
        std::cout << " ]\n";
    }

    std::unordered_map<T,int> create_freq_map(){
        // static_assert check at compile time (so no extra cost at runtime)
        static_assert(
            std::is_same<T, int>::value || std::is_same<T, std::string>::value,
            "T must be int or std::string to use create_freq_map"
        );
        std::unordered_map<T,int> mp;
        for(int i=0;i<length;i++){
            mp[data[i]]++;
        }
        return mp;
    }


};
}

#endif