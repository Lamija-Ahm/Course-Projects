#include <iostream>
#include <string>
#include "Heap.hpp" 

int main() {
    Heap<int> heap;
    heap.insert(10).insert(20).insert(5).insert(30).insert(15);
    std::cout << heap << std::endl;
    std::cout << "Max: " << heap.max() << std::endl;
    heap.removeMax();
    std::cout << heap << std::endl;
    std::cout << "Min element: " << heap.min() << std::endl;
    heap.removeMin();
    std::cout << heap << std::endl;
  
    std::cout << "Is empty? " << (heap.empty() ? "Yes" : "No") << std::endl;

    Heap<int> heapCopy = heap;
    std::cout << "Heap copy: " << heapCopy << std::endl;

   
    Heap<int> heapMove = std::move(heap);
    std::cout << "Heap after move: " << heap << std::endl;
    std::cout << "Heap moved to: " << heapMove << std::endl;
    heap = heapCopy;
    std::cout << "Heap after copy assignment: " << heap << std::endl;

    heap = std::move(heapMove);
    std::cout << "Heap after move assignment: " << heap << std::endl;
    std::cout << "Heap moved from (should be empty): " << heapMove << std::endl;

    return 0;
}
