#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class MaxHeap {
private:
    std::vector<T> data;
public:
    void push(const T& item);
    // Removes the largest element in the heap
    void pop();
    // Returns the largest element in the heap (but does not remove it)
    T const& top() const;
    std::size_t size() const;
    void heapify(int idx);
};

template <typename T>
void MaxHeap<T>::push(const T& item) {
    data.push_back(item);
    std::size_t index = data.size() - 1;
    while (index != 0) {
        std::size_t parent_index = (index - 1) / 2;
        T& current = data[index];
        T& parent = data[parent_index];
        if (current <= parent) {
            break;
        }
        std::swap(current, parent);
        index = parent_index;
    }
}

template <typename T>
void MaxHeap<T>::pop() {
    if (data.empty()) {
        throw std::out_of_range("heap is empty");
    }

    // Swap the “best” node with last leaf node
    std::swap(data[0], data[data.size()-1]);

    // Delete the very last leaf node
    data.pop_back();

    // trickling down
    heapify(0);
    
}

template <typename T>
T const& MaxHeap<T>::top() const {
    if (data.empty()) {
        throw std::out_of_range("heap is empty");
    }
    return data[0];
}

template <typename T>
std::size_t MaxHeap<T>::size() const {
    return data.size();
}

template <typename T>
void MaxHeap<T>::heapify(int idx){
    size_t right_child = 2*idx + 2;
    size_t left_child = 2*idx + 1;

    // stop when last node
    if(left_child >= data.size() and right_child >= data.size()){ 
        return;
    } 
    size_t biggerChildID = left_child;

    // compare left and right child
    if(right_child > 0 and right_child < data.size()) {  // check for valid right child
        if(data[right_child] > data[biggerChildID]){
            biggerChildID = right_child;
        }
    }
    
    // compare root and best child
    if(data[idx] < data[biggerChildID]){
        std::swap(data[idx], data[biggerChildID]);
        heapify(biggerChildID);
    } 
}
