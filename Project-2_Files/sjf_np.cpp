#include "sjf_np.h"
#include <algorithm>
#include <vector>

void SJF_NP::add_process(const Process &P)
{
    all_Processes.push_back(P);
}

void SJF_NP::run(int current_time)
{
    while (!all_Processes.empty() || !ready.empty())
    {
        // move arrived processes
        move_arrived_processes(all_Processes, ready, current_time);

        if (ready.empty())
        {
            current_time++;
            continue;
        }

        sort(ready.begin(), ready.end(),
             [](const Process &a, const Process &b)
             { return a.get_burst_time() < b.get_burst_time(); });

        Process p = ready.front();
        ready.erase(ready.begin());

        if (p.get_start_time() == -1)
            p.set_start_time(current_time);

        gantt.push_back({p.get_pid(), current_time, current_time + p.get_remaining_time()});

        current_time += p.get_remaining_time();
        p.set_remaining_time(0);
        p.set_completion_time(current_time);
        completed.push_back(p);
    }
}

bool SJF_NP::has_pending() const
{
    return !ready.empty() || !all_Processes.empty();
}

std::vector<Process> SJF_NP::get_completed() const
{
    return completed;
}

/*SJF Non-Preemptive — logic summary:
Goal: Run the process with the shortest total burst time first.
ready: all arrived processes waiting to run.

1.At each current_time, move all processes with arrival_time ≤ current_time from all_Processes → ready.
2.If ready is empty, increment current_time and repeat.
3.Sort ready by burst_time in ascending order.
4.Select the first process (shortest job).
5.If it is running for the first time, set start_time = current_time.
6.Run the process to completion (current_time += remaining_time, set remaining = 0).
7.Set completion_time and move the process to completed.
8.Repeat until both all_Processes and ready are empty.

Why non-preemptive:
Once a process starts, it runs till finish — no interruption even if a shorter job arrives later.
*/
