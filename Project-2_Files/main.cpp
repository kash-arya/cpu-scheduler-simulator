#include <iostream>
#include <vector>

#include "process.h"
#include "simulation.h"
#include "fcfs.h"
#include "sjf_np.h"
#include "sjf_p.h"
#include "priority.h"
#include "round_robin.h"

using namespace std;

/*
  Returns the same set of processes every time.
  This ensures ALL schedulers run on IDENTICAL input,
  which is required for fair comparison.
*/
vector<Process> get_processes()
{
    return {
        Process(1, 0, 5, 1),
        Process(2, 1, 4, 2),
        Process(3, 2, 2, 3)
    };
}

int main()
{
    Simulation sim;

    // ---------- FCFS ----------
    {
        FCFS sched;
        for (const auto &p : get_processes())
            sched.add_process(p);

        cout << "\nFCFS:\n";
        sim.run(sched, 0);
    }

    // ---------- SJF (Non-Preemptive) ----------
    {
        SJF_NP sched;
        for (const auto &p : get_processes())
            sched.add_process(p);

        cout << "\nSJF Non-Preemptive:\n";
        sim.run(sched, 0);
    }

    // ---------- SJF (Preemptive / SRTF) ----------
    {
        SJF_P sched;
        for (const auto &p : get_processes())
            sched.add_process(p);

        cout << "\nSJF Preemptive (SRTF):\n";
        sim.run(sched, 0);
    }

    // ---------- Priority (Non-Preemptive, dynamic arrival) ----------
    {
        Priority sched;
        for (const auto &p : get_processes())
            sched.add_process(p);

        cout << "\nPriority Scheduling:\n";
        sim.run(sched, 0);
    }

    // ---------- Round Robin ----------
    {
        RoundRobin sched(2); // time quantum = 2
        for (const auto &p : get_processes())
            sched.add_process(p);

        cout << "\nRound Robin (Q = 2):\n";
        sim.run(sched, 0);
    }

    return 0;
}
