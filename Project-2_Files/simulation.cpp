#include "simulation.h"
#include <iomanip>
using namespace std;
void Simulation::run(Scheduler &scheduler, int start_time)
{
    scheduler.run(start_time);
    auto finished = scheduler.get_completed();
    if (finished.empty())
        return;
    int total_tat = 0;
    int total_wt = 0;
    int total_rt = 0;
    for (const auto& p : finished)
    {
        int turnaround = p.get_completion_time() - p.get_arrival_time();
        total_tat += turnaround;
        int waiting_time = turnaround - p.get_burst_time();
        total_wt += waiting_time;
        int response = p.get_start_time() - p.get_arrival_time();
        total_rt += response;
    }
    cout << "Average Turnaround Time: ";
    cout << (double)total_tat / finished.size() << endl; // You are doing integer division. Averages will be truncated. Fix: cast once.
    cout << "Average Waiting Time: ";
    cout << (double)total_wt / finished.size() << endl;
    cout << "Average Response Time: ";
    cout << (double)total_rt / finished.size() << endl;

    // ---- Gantt Chart ----
    auto chart = scheduler.get_gantt();

    // merge consecutive blocks (already discussed)
    vector<GanttBlock> merged;
    for (const auto &b : chart)
    {
        if (!merged.empty() && merged.back().pid == b.pid)
            merged.back().end_time = b.end_time;
        else
            merged.push_back(b);
    }

    if (!merged.empty())
    {
        cout << "\nGantt Chart:\n";
        // Print process blocks
        for (const auto &b : merged)
            cout << "| P" << b.pid << " ";
        cout << "|\n";

        // Print timeline with fixed width
        cout << setw(2) << merged[0].start_time;
        for (const auto &b : merged)
            cout << setw(5) << b.end_time;
        cout << "\n";
    }
}
/*Why averages are needed?
Scheduling algorithms are compared, not judged per process.
One process tells nothing; averages summarize overall performance.
OS textbooks, exams, and interviews always compare algorithms using averages:
Avg Waiting Time → CPU efficiency
Avg Turnaround Time → system throughput
Avg Response Time → user interactivity
Without averages, you cannot say which scheduler is better.*/
