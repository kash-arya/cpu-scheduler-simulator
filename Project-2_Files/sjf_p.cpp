#include "sjf_p.h"
#include <algorithm>

void SJF_P::add_process(const Process &P)
{
    all_Processes.push_back(P);
}

void SJF_P::run(int current_time)
{
    while (!all_Processes.empty() || !ready.empty())
    {
        // 1. Add arrivals
        move_arrived_processes(all_Processes, ready, current_time);

        // 2. If no ready process, advance time
        if (ready.empty())
        {
            current_time++;
            continue;
        }

        // 3. Re-sort EVERY TIME UNIT
        sort(ready.begin(), ready.end(),
             [](const Process &a, const Process &b)
             {
                 return a.get_remaining_time() < b.get_remaining_time();
             });

        // 4. Pick shortest remaining job
        Process p = ready.front();
        ready.erase(ready.begin());

        if (p.get_start_time() == -1)
            p.set_start_time(current_time);

        // 5. Execute EXACTLY 1 unit
        gantt.push_back({p.get_pid(), current_time, current_time + 1});
        p.set_remaining_time(p.get_remaining_time() - 1);
        current_time++;

        // 6. Finish or requeue
        if (p.get_remaining_time() == 0)
        {
            p.set_completion_time(current_time);
            completed.push_back(p);
        }
        else
        {
            ready.push_back(p);
        }
    }
}

bool SJF_P::has_pending() const
{
    return !ready.empty() || !all_Processes.empty();
}

std::vector<Process> SJF_P::get_completed() const
{
    return completed;
}

/*SJF Preemptive (SRTF) — logic summary:

Goal: Always run the process with shortest remaining time among arrived ones.

Data structures:
all_Processes → processes not yet arrived
ready → arrived but unfinished
completed → finished
gantt → execution timeline (1 unit slices)

Algorithm steps (exact runtime order):

1️⃣ Arrival handling (every time unit)
Move all processes with
arrival_time ≤ current_time
from all_Processes → ready.

2️⃣ CPU idle handling: If ready is empty: current_time++
repeat loop

3️⃣ Re-sort ready queue (preemption point)
Sort ready by shortest remaining_time (optional improvement later) arrival time & PID
This enables preemption.

4️⃣ Select process: Pick the first process (shortest remaining job).
If start_time == -1, set it.

5️⃣ Execute exactly 1 time unit
Record Gantt slice:(pid, current_time, current_time + 1)
Decrement remaining_time.
current_time++.

6️⃣ Finish or requeue:
If remaining_time == 0:
    set completion_time
    move to completed
Else: push back into ready

7️⃣ Repeat until done: Loop continues until all_Processes and ready are empty.

Why it’s preemptive:
Because each new arrival can reorder the queue — a shorter new process can preempt the current one.
*/
