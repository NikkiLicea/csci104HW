#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
void initSched(const AvailabilityMatrix& avail, DailySchedule& sched);  // initialize sched to invalid IDs
bool validSched(const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t curr_row); // check if maxShifts has been reached
bool combo(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t row);  // all combinations of available workers
bool fullSched(const size_t dailyNeed, DailySchedule& sched);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
){
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    initSched(avail, sched);  // init sched to include correct amount of empty vectors
    return combo(avail, dailyNeed, maxShifts, sched, 0);
}

// void initSched(DailySchedule& sched){
//     for (size_t i = 0; i < sched.size(); i++){
//         for (size_t j = 0; j < sched[i].size(); j++){
//             sched[i][j] = INVALID_ID;
//         }
//     }
// }

void initSched(const AvailabilityMatrix& avail, DailySchedule& sched){
    for (size_t i = 0; i < avail.size(); i++){
        std::vector<Worker_T> vect;
        sched.push_back(vect);
    }
}

bool validSched(const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t curr_row){
    if(curr_row == 0){
        return true;
    }
    for (size_t c = 0; c < dailyNeed; c++){  // iterate through newly filled row
        Worker_T worker = sched[curr_row][c];  // worker in new row
        size_t numShifts = 1;  // num shifts worked by worker (includes curr_row shift)
        for(size_t r = 0; r < curr_row; r++){
            if(find(sched[r].begin(), sched[r].end(), worker) != sched[r].end()){  // found worker in row
                numShifts++;
            }
            if(numShifts > maxShifts){  // worker has too many shifts
                return false;
            }
        }
    }
    return true;
}

bool fullSched(const size_t dailyNeed, DailySchedule& sched){
    if(sched.size() == 0){
        return false;
    }
    for(size_t r = 0; r < sched.size(); r++){
        if(sched[r].size() < dailyNeed){
            return false;
        }
    }
    return true;
}

bool combo(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t row){
    if(fullSched(dailyNeed, sched)){ 
      return true;  
    }
    else if(count(avail[row].begin(), avail[row].end(), 1) < (int)dailyNeed){  // not enough workers
        return false;
    }
    else if(avail[row].size() == 1 and avail[row][0] == 1){
        DailySchedule schedTemp = sched;
        schedTemp[row].push_back(0);
        if(!validSched(dailyNeed, maxShifts, schedTemp, row)){
            return false;
        }
        else if((row + 1) < avail.size()){  // continue onto next row
            return combo(avail, dailyNeed, maxShifts, schedTemp, ++row);
        }
    }
    for(size_t c = 0; c < avail[row].size() - 1; c++){
        DailySchedule schedTemp = sched;
        if(avail[row][c] == 1){
            schedTemp[row].push_back(c);
        }
        AvailabilityMatrix availTemp = avail;
        availTemp.erase(availTemp.begin());
        if(!validSched(dailyNeed, maxShifts, sched, row)){
            return false;
        }
        else if((schedTemp[row].size() - 1) < dailyNeed and validSched(dailyNeed, maxShifts, schedTemp, row)){  // sched row not full 
            return combo(availTemp, dailyNeed, maxShifts, schedTemp, row);
        }
        else if(validSched(dailyNeed, maxShifts, schedTemp, row)){  // continue onto next row
            return combo(availTemp, dailyNeed, maxShifts, schedTemp, ++row);
        }
    }
    return true;
}

// void go(int offset, int k) {
//   if (k == 0) {
//     pretty_print(combination);
//     return;
//   }
//   for (int i = offset; i <= people.size() - k; ++i) {
//     combination.push_back(people[i]);
//     go(i+1, k-1);
//     combination.pop_back();
//   }
// }


