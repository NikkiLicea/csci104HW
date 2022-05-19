#include "stones.h"
#include "max_heap.h"

int lastStoneWeight(std::vector<int>& stones) {
    MaxHeap<int> heap;

    // create heap
    for(size_t i = 0; i < stones.size(); i++){
        heap.push(stones[i]);
    }
    
    while(heap.size() > 1){
        // find heaviest rocks
        int x = heap.top();
        heap.pop();
        int y = heap.top();
        
        if(x == y){  // destroy both rocks
            heap.pop();
            
        }
        else{
            heap.pop();
            heap.push(x-y);
        }
    }
    
    if(heap.size() == 1){
        return heap.top();
    }
    return 0;
}
