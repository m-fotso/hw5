#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool fillShifts(size_t dayNeed, size_t dayToWork, Worker_T currWorker, map<Worker_T, size_t>& maxShifts, AvailabilityMatrix avail, DailySchedule& sched, size_t workIndex, size_t ms);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    
    // Add your code below
    map<Worker_T, size_t> shifts;
    for(size_t i=0; i<avail.size(); i++) {
        std::vector<Worker_T> k;
        for(size_t j=0; j<avail[i].size(); j++) {
            shifts[j] = maxShifts;
            if(j < dailyNeed) {
               k.push_back(-1); 
            }
        }
        sched.push_back(k);
    }
    
    return fillShifts(sched[0].size(), 0, 0, shifts, avail, sched, 0, maxShifts);
    
    
}

bool fillShifts(size_t dayNeed, size_t dayToWork, Worker_T currWorker, map<Worker_T, size_t>& maxShifts, AvailabilityMatrix avail, DailySchedule& sched, size_t workIndex, size_t ms) {
    if(dayToWork == sched.size()) {
        return true;
    }
    if(maxShifts.find(currWorker) == maxShifts.end()) {
        if(dayToWork != sched.size()-1) {
            return fillShifts(dayNeed, dayToWork, 0, maxShifts, avail, sched, workIndex, ms);
        } else {
            return false;
        }
    }
    for(size_t i=0; i<maxShifts.size(); i++) {
        sched[dayToWork][workIndex] = i;
        if(avail[dayToWork][i] && maxShifts[i] > 0){
            
            maxShifts[i]--;
            if(workIndex < dayNeed-1) {
                if(fillShifts(dayNeed, dayToWork, i, maxShifts, avail, sched, workIndex+1, ms) == true) {
                    return true;
                } else {
                    maxShifts[i]++;
                    return false;
                }
            } else {
                if(fillShifts(dayNeed, dayToWork+1, 0, maxShifts, avail, sched, 0, ms) == true) {
                    return true;
                } else {
                    maxShifts[i]++;
                    return false;
                }
            }
        }
    }
     //if you reach 0 shifts for that worker

    return false;
}

