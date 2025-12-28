#include "round_robin.h"
#include <algorithm>

void RoundRobin::add_process(const Process &P)
{
    all_Processes.push_back(P);
    std::sort(all_Processes.begin(), all_Processes.end(),
              [](const Process &a, const Process &b)
              {
                  return a.get_arrival_time() < b.get_arrival_time();
              });
}

void RoundRobin::run(int current_time)
{
    while (!all_Processes.empty() || !ready.empty())
    {
        move_arrived_processes(all_Processes, ready, current_time);

        if (ready.empty())
        {
            current_time++;
            continue;
        }
        else
        {
            Process p = ready.front();
            ready.erase(ready.begin());
            if (p.get_start_time() == -1)
                p.set_start_time(current_time);

            int slice_start = current_time;

            int slice = std::min(time_quantum, p.get_remaining_time());
            p.set_remaining_time(p.get_remaining_time() - slice);
            current_time += slice;

            int slice_end = current_time;
            gantt.push_back({p.get_pid(), slice_start, slice_end});

            // adding arrivals that came during the slice
            for (size_t i = 0; i < all_Processes.size();) // Reason for this loop mid way→ ensures fairness if new processes arrive mid-quantum.
            {
                if (all_Processes[i].get_arrival_time() <= current_time)
                {
                    ready.push_back(all_Processes[i]);
                    all_Processes.erase(all_Processes.begin() + i);
                }
                else
                    i++;
            }

            if (p.get_remaining_time() == 0)
            {
                p.set_completion_time(current_time);
                completed.push_back(p);
            }
            else
                ready.push_back(p);
        }
    }
}

bool RoundRobin::has_pending() const
{
    return !ready.empty() || !all_Processes.empty();
}

std::vector<Process> RoundRobin::get_completed() const
{
    return completed;
}

/*
Round Robin — Logic Summary:
Goal: Each process gets equal CPU time in cycles until all complete.
Key Points:
1. all_Processes: yet to arrive.
2. ready: arrived and waiting.
3. At each time step:
   - Move newly arrived processes(all processes are sorted as soon as a new one is created) (arrival ≤ current_time) to ready.
   - If ready is empty → idle CPU → current_time++.
   - Else run the front process for time_quantum or remaining time, whichever is smaller.
4. If process still has remaining time → push it to back of ready.
5. If finished → record completion_time and store in completed.

Reasons for design choices:
- deque used for push_back + pop_front operations.
- current_time advanced by slice to simulate partial CPU use.
- arrivals checked again after each quantum to handle mid-quantum arrivals correctly.
- has_pending() checks both ready and all_Processes to avoid premature exit.
*/
