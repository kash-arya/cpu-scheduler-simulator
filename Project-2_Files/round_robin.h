#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H
#include "scheduler.h"
// #include <queue>

class RoundRobin : public Scheduler
{
    std::vector<Process> all_Processes;
    std::vector<Process> ready;
    std::vector<Process> completed;
    int time_quantum;

public:
    RoundRobin(int tq) : time_quantum(tq) {}
    void add_process(const Process &P) override;
    void run(int current_time) override;
    bool has_pending() const override;
    std::vector<Process> get_completed() const override;
};

#endif
