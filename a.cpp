#include "include/maydsa.hpp"
using namespace MayDSA;

int main() {
    // 🔗 Linked List
    LinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);
    list.insert(1, 15); // Insert at position 1
    std::cout << "Linked List: ";
    list.print();
    std::cout << "Find 15 at index: " << list.find(15) << "\n\n";

    // 📦 Vector
    Vector<std::string> vec;
    vec.push_back("apple");
    vec.push_back("banana");
    vec.push_back("apple");
    vec.print();
    std::cout << "Size of vector: " << vec.size() << "\n";
    std::cout << "Find 'banana' at index: " << vec.find("banana") << "\n";
    auto freq_map = vec.create_freq_map();
    std::cout << "Frequency map:\n";
    for (auto& [k, v] : freq_map) {
        std::cout << "  " << k << ": " << v << "\n";
    }
    std::cout << "\n";

    // 🔁 DSU
    DSU<int> dsu;
    // dsu.unite(1, 2);
    // dsu.unite(3, 4);
    // std::cout << "DSU find(2): " << dsu.find(2) << "\n";
    // std::cout << "DSU find(4): " << dsu.find(4) << "\n";

    // 🔼 Min Heap
    MinHeap minHeap;
    minHeap.push(10);
    minHeap.push(5);
    minHeap.push(8);
    std::cout << "MinHeap top: " << minHeap.top() << "\n";
    minHeap.pop();
    std::cout << "After pop, MinHeap top: " << minHeap.top() << "\n\n";

    // 🔽 Max Heap
    MaxHeap maxHeap;
    maxHeap.push(10);
    maxHeap.push(20);
    maxHeap.push(15);
    std::cout << "MaxHeap top: " << maxHeap.top() << "\n";
    maxHeap.pop();
    std::cout << "After pop, MaxHeap top: " << maxHeap.top() << "\n\n";

    // 🌐 Graph (Undirected)
    Graph<char> g(false);
    g.add_edge('A', 'B', 4);
    g.add_edge('A', 'C', 3);
    g.add_edge('B', 'C', 1);
    g.add_edge('C', 'D', 5);
    std::cout << "Graph:\n";
    g.print();

    std::cout << "BFS from A to D: " << (g.bfs('A', 'D') ? "Yes" : "No") << "\n";
    std::cout << "DFS from A to D: " << (g.dfs('A', 'D') ? "Yes" : "No") << "\n";
    std::cout << "Has cycle: " << (g.has_cycle() ? "Yes" : "No") << "\n";

    // Export graph visualization (DOT and PNG)
    g.export_png("graph_output.png");  // Ensure `dot` is installed

    return 0;
}