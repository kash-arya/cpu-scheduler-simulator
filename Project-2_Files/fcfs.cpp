#include "fcfs.h" // First Come First Serve

void FCFS::add_process(const Process &P)
{
    all_Processes.push_back(P);
}

void FCFS::run(int current_time)
{
    while (!all_Processes.empty() || !ready.empty())
    {
        // Move arrived processes to ready queue
        move_arrived_processes(all_Processes, ready, current_time);

        // If CPU idle, advance time
        if (ready.empty())
        {
            current_time++;
            continue;
        }

        // Execute next process
        Process p = ready.front();
        ready.erase(ready.begin());

        if (p.get_start_time() == -1)
            p.set_start_time(current_time);

        gantt.push_back({p.get_pid(),
                         current_time,
                         current_time + p.get_remaining_time()});

        current_time += p.get_remaining_time();
        p.set_remaining_time(0);
        p.set_completion_time(current_time);
        completed.push_back(p);
    }
}

bool FCFS::has_pending() const
{
    return !ready.empty() || !all_Processes.empty();
}

std::vector<Process> FCFS::get_completed() const
{
    return completed;
}

/*Updated FCFS logic steps (correct & consistent)

FCFS — Dynamic Arrival Version
1. add_process()→ store processes in all_Processes.

2. run() loop continues while: future processes exist or ready queue is non-empty.

3. At each time: Move all processes with arrival_time ≤ current_time from all_Processes → ready.

4. If ready is empty: CPU idle → current_time++.

5.Else:
Pop front process from ready.
If first execution → set start_time.
Record one Gantt block.
Run process till completion.
Set completion_time, move to completed.

6.Repeat until all processes finish.
*/
