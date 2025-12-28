#ifndef PRIORITY_H
#define PRIORITY_H
#include "scheduler.h"

class Priority : public Scheduler
{
    std::vector<Process> all_Processes;
    std::vector<Process> ready;
    std::vector<Process> completed;

public:
    void add_process(const Process &P) override;
    void run(int current_time) override;
    bool has_pending() const override;
    std::vector<Process> get_completed() const override;
};

#endif
