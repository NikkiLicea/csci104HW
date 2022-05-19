#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> h;
  PComparator c_;
  int m_;
  void heapify(int idx);
};

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c){
  m_ = m;
  c_ = c;
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){};

// Add implementation of member functions here
template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(int idx){
  size_t left_child = 2*idx + 1;
  size_t right_child = 2*idx + 2;
    
  // stop when last node
  if(left_child >= this->h.size() and right_child >= this->h.size()){ 
      return;
  } 
  size_t biggerChildID = left_child;

  // compare left and right child
  if(right_child > 0 and right_child < this->h.size()) {  // check for valid right child
    if(c_(this->h[right_child], this->h[biggerChildID])){  // when right is better than left
      biggerChildID = right_child;
    }
  }
  
  // compare root and best child
  if(c_(this->h[biggerChildID], this->h[idx])){  // when best child is greater than root
    std::swap(this->h[idx], this->h[biggerChildID]);
    heapify(biggerChildID);
  } 
}


// We will start top() for you to handle the case of 
// calling top on an empty heap - DONE
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){  // throw the appropriate exception
    throw std::underflow_error("Heap is empty");
  }

  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return this->h.front();
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap - DONE
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop(){
  if(empty()){  // throw the appropriate exception
    throw std::underflow_error("Stack is empty");
  }
  // Swap the “best” node with last leaf node
  std::swap(this->h[0], this->h[this->h.size()-1]);

  // Delete the very last leaf node
  this->h.pop_back();

  // trickling down
  heapify(0);
}

// DONE
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
  this->h.push_back(item);  // add to vector
  size_t index = this->h.size() - 1;  // get index of item

  while (index != 0) {
    size_t parent_index = (index - 1) / 2;  // get parent index
    T& current = this->h[index];  // get current value
    T& parent = this->h[parent_index];  // get parent value
    if(!c_(current, parent)){  // break when current in correct place
      break;
    }
    std::swap(current, parent);  // swap if current is better than parent
    index = parent_index;  // update index
  }
}

// DONE
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
  return this->h.std::vector<T>::empty();
}

#endif

