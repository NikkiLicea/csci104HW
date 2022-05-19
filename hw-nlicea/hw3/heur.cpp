#include <cmath>
#include "heur.h"
#include <vector>
#include <set>
using namespace std;

// Complete
size_t BFSHeuristic::compute(const Board& b)
{
    return 0U;
}


// To be completed
size_t DirectHeuristic::compute(const Board& b){
    size_t vehiclesFound = 0;
    Vehicle a = b.escapeVehicle();
    for(int c = a.startc + 1; c < b.size(); c++){  // start at a vehicle column and move right to end of board
        if(b.at(a.startr, c) != '.' and b.at(a.startr, c) != 'a'){
            vehiclesFound++;
        }
    }
    return vehiclesFound;
}

// To be completed
size_t IndirectHeuristic::compute(const Board& b){
    DirectHeuristic d;
    int numDirect = d.compute(b);
    int numIndirect = 0;

    // Vehicle a = b.escapeVehicle();

    // bool roomAbove = false;
    // bool roomBelow = false; 
    // int top_room = a.startr;
    // int btm_room = b.size() - a.startr - 1;

    // if(top_room >= a.length){  // check if there is the space to move
    //     roomAbove = true;
    // }
    // else if(btm_room >= a.length){
    //     roomBelow = true;
    // }

    // if(roomAbove and !roomBelow){  // only room above
    //     for(int r = a.startr - 1; r >= a.length - 1; r--){  // iterate through above rows
    //         if(b.at(r, ) != '.' and b.at(a.startr, c) != 'a')
    //     }
    // }

    return numDirect + numIndirect;
}

