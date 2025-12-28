#include "priority.h"
#include <algorithm>

void Priority::add_process(const Process &P)
{
    all_Processes.push_back(P);
}

void Priority::run(int current_time)
{
    while (!all_Processes.empty() || !ready.empty())
    {
        move_arrived_processes(all_Processes, ready, current_time);

        std::sort(ready.begin(), ready.end(), [](const Process &a, const Process &b)
                  { return a.get_priority() < b.get_priority(); });

        Process p = ready.front();
        ready.erase(ready.begin());
        if (p.get_start_time() == -1)
            p.set_start_time(current_time);
        gantt.push_back({ p.get_pid(), current_time, current_time + p.get_remaining_time() });
        current_time += p.get_remaining_time();
        p.set_remaining_time(0);
        p.set_completion_time(current_time);
        completed.push_back(p);
    }
}

bool Priority::has_pending() const
{
    return !ready.empty();
}

std::vector<Process> Priority::get_completed() const
{
    return completed;
}

/*Priority — logic summary:
Goal: Always run the process with the highest Priority (least number) among arrived ones.

all_Processes: yet-to-arrive jobs.
ready: arrived but unfinished jobs.

Step-by-step:
1.At each time unit, move all processes whose arrival ≤ current_time from all_Processes → ready.
2️.Sort ready by priority to pick the highest priority one.
3️.If process runs for the first time → set start_time.
4️.A process once executed will tend to finish completely since this is non-preemptive in nature.
5️. After a process has run to its completion, add it to the completed.
*/
