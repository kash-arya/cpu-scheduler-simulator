#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "process.h"

struct GanttBlock
{
    int pid;
    int start_time;
    int end_time;
};

class Scheduler
{
protected:
    std::vector<GanttBlock> gantt;

    // 🔹 NEW: shared arrival handler
    void move_arrived_processes(std::vector<Process> &all_Processes,std::vector<Process> &ready,int current_time)
    {
        for (size_t i = 0; i < all_Processes.size();)
        {
            if (all_Processes[i].get_arrival_time() <= current_time)
            {
                ready.push_back(all_Processes[i]);
                all_Processes.erase(all_Processes.begin() + i);
            }
            else
                i++;
        }
    }

public:
    virtual void add_process(const Process &) = 0;
    virtual void run(int current_time) = 0;
    virtual bool has_pending() const = 0;
    virtual std::vector<Process> get_completed() const = 0;

    const std::vector<GanttBlock> &get_gantt() const { return gantt; }

    virtual ~Scheduler() = default;
};

#endif
