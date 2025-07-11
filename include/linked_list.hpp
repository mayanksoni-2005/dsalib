#ifndef MAYDSA_LINKED_LIST_HPP
#define MAYDSA_LINKED_LIST_HPP

#include <iostream>
#include <stdexcept>
#include <unordered_set>

namespace MayDSA{

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val): data(val), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t length;

public:
    // Constructor and destructor
    LinkedList(): head(nullptr), tail(nullptr), length(0) {}
    ~LinkedList();

    // Core operations
    void push_front(const T& val);
    void push_back(const T& val);
    void pop_front();
    void pop_back();
    void insert(size_t pos, const T& val);
    void remove(size_t pos);
    void reverse();
    bool havecycle() const;

    // Utility
    size_t size() const;
    Node* accessHead() const;
    int find(const T& val) const;
    void print() const;
};

template<typename T>
MayDSA::LinkedList<T>::~LinkedList() {
    std::unordered_set<Node*> visited;
    while (head) {
        if (visited.count(head)) break; // Detected cycle, stop
        visited.insert(head);
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    length = 0;
}


template<typename T>
void MayDSA::LinkedList<T>::push_front(const T& val) {
    Node* new_node = new Node(val);
    new_node->next = head;
    head = new_node;
    if (tail == nullptr) tail = head;
    length++;
}

template<typename T>
void MayDSA::LinkedList<T>::push_back(const T& val) {
    Node* new_node = new Node(val);
    if (tail) {
        tail->next = new_node;
        tail = new_node;
    } else {
        head = tail = new_node;
    }
    length++;
}

template<typename T>
void MayDSA::LinkedList<T>::pop_front() {
    if (!head) throw std::out_of_range("List is empty");
    Node* temp = head;
    head = head->next;
    delete temp;
    if (!head) tail = nullptr;
    --length;
}

template<typename T>
void MayDSA::LinkedList<T>::pop_back() {
    if (!head) throw std::out_of_range("List is empty");
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node* curr = head;
        while (curr->next != tail) curr = curr->next;
        delete tail;
        tail = curr;
        tail->next = nullptr;
    }
    --length;
}


template<typename T>
void MayDSA::LinkedList<T>::insert(size_t pos, const T& val) {
    if (pos > length) throw std::out_of_range("Index out of range");
    if (pos == 0) return push_front(val);
    if (pos == length) return push_back(val);

    Node* curr = head;
    for (size_t i = 0; i < pos - 1; ++i) curr = curr->next;
    Node* new_node = new Node(val);
    new_node->next = curr->next;
    curr->next = new_node;
    ++length;
}

template<typename T>
void MayDSA::LinkedList<T>::remove(size_t pos) {
    if (pos >= length) throw std::out_of_range("Index out of range");
    if (pos == 0) return pop_front();
    
    Node* curr = head;
    for (size_t i = 0; i < pos - 1; ++i) curr = curr->next;
    Node* temp = curr->next;
    curr->next = temp->next;
    if (temp == tail) tail = curr;
    delete temp;
    --length;
}

template<typename T>
void MayDSA::LinkedList<T>::reverse() {
    Node* prev = nullptr;
    Node* curr = head;
    tail = head;
    while (curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

template<typename T>
size_t MayDSA::LinkedList<T>::size() const {
    return length;
}

template<typename T>
typename MayDSA::LinkedList<T>::Node* MayDSA::LinkedList<T>::accessHead() const {
    return head;
}



template<typename T>
int MayDSA::LinkedList<T>::find(const T& val) const {
    Node* curr = head;
    int idx = 0;
    while (curr) {
        if (curr->data == val) return idx;
        curr = curr->next;
        ++idx;
    }
    return -1; // not found
}

template<typename T>
void MayDSA::LinkedList<T>::print() const {
    Node* curr = head;
    std::cout << "[ ";
    while (curr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << "]\n";
}

template<typename T>
bool MayDSA::LinkedList<T>::havecycle() const{
    Node* slow=head;
    Node* fast=head;
    while(fast!=NULL && fast->next!=NULL){
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast){
            return true;
        }
    }
    return false;
}





} // namespace MayDSA

#endif
