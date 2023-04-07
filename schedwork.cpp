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
bool backtrack(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    const size_t day,
    std::vector<size_t>& counts
);

// type for the ID of a worker
typedef unsigned int Worker_T;

// n-by-k Matrix of each of the k workers' availability over an n-day period
typedef std::vector<std::vector<bool>> AvailabilityMatrix;

// n-by-d matrix with the d worker IDs who are scheduled 
// to work on each of the n days
typedef std::vector<std::vector<Worker_T>> DailySchedule;


/**
 * @brief Produces a work schedule given worker availability,
 *        the number of needed workers per day, and the maximum 
 *        shifts any single worker is allowed. Returns true if
 *        and the valid schedule if a solution exists, and false
 *        otherwise. 
 * You MAY define helper functions in schedworker.cpp
* You MUST use a recursive approach that follows the general backtracking structure 
 * @param [in]  avail n x k vector of vectors (i.e. matrix) of the availability
 *                    of the k workers for each of the n days
 * @param [in]  dailyNeed Number of workers needed per day (aka d)
 * @param [in]  maxShifts Maximum shifts any worker is allowed over 
 *                        the n day period (aka m)
 * @param [out] sched n x d vector of vectors indicating the d workers
 *                    who are scheduled to work on each of the n days
 * @return true if a solution exists; sched contains the solution
 * @return false if no solution exists; sched is undefined (can be anything)
 */
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
	if(avail.size() == 0U)
	{
		return false;
  }
  
	sched.clear();
  

  sched.resize(avail.size());
  std::vector<size_t> counts(avail[0].size(), 0);

  // backtrackinggg
  if ( backtrack(avail, dailyNeed, maxShifts, sched, 0, counts) ) 
	{
    return true;
  } 
	else 
	{
    return false;
  }

}


bool backtrack(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    const size_t day,
    std::vector<size_t>& counts
) 
{
  // all days scheduled!
  if (day == avail.size()) 
	{
    return true;
  }

  // try all workers
  for (size_t worker = 0; worker < avail[day].size(); ++worker) 
	{
    // is worker available?
    if (avail[day][worker]) 
		{
      // exceed max shifts?
      if (counts[worker] < maxShifts) 
			{
				// push the worker to the schedule
        sched[day].push_back(worker);
        counts[worker]++;

        // if day is full, move to next day
				if (sched[day].size() == dailyNeed) 
				{
					if (backtrack(avail, dailyNeed, maxShifts, sched, day+1, counts)) 
					{
						return true;
					}
					else
					{
						// backtrack if it don't worker
            sched[day].pop_back();
            counts[worker]--;
					}
				}

                
      }
  	}
	}

    // can't schedule this day so backtrack!!
    return false;
}
