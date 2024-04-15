#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool backtrack(
    const AvailabilityMatrix& avail, 
    size_t dailyNeed, size_t maxShifts,
    DailySchedule& sched, 
    size_t day, 
    size_t shift, 
    std::vector<size_t>& shifts);

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
    // Add your code belowcd
    

    // Initialize schedule with INVALID_ID and vector to track shifts
    sched.resize(avail.size(), std::vector<Worker_T>(dailyNeed, INVALID_ID));
    std::vector<size_t> shifts(avail[0].size(), 0);

    // Start backtracking to generate the schedule
    return backtrack(avail, dailyNeed, maxShifts, sched, 0, 0, shifts);

}

// Backtracking function to assign workers to shifts
bool backtrack(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts,
               DailySchedule& sched, size_t day, size_t shift, std::vector<size_t>& shifts) {
    
    // Base case: if all days are filled
    if (day == avail.size()) {
        return true;
    }

    // Iterate over each worker
    for (size_t worker = 0; worker < avail[day].size(); ++worker) {

        // Check if the worker is available and hasn't reached the maximum shifts
        if (shifts[worker] < maxShifts && avail[day][worker]) {

            // Assign the worker to the shift
            shifts[worker]++;
            sched[day][shift] = worker;

            // Calculate the index of the next day and shift
            size_t nextDay = (shift + 1) / dailyNeed + day;
            size_t nextShift = (shift + 1) % dailyNeed;

            // Recursively call backtrack for the next shift
            if (backtrack(avail, dailyNeed, maxShifts, sched, nextDay, nextShift, shifts)) {
                return true; 
            }

            // Backtrack
            shifts[worker]--;
            sched[day][shift] = INVALID_ID;
        }
    }

    // No valid assignment found for the current day and shift
    return false;
}