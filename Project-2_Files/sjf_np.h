#ifndef SJF_NP_H
#define SJF_NP_H

#include "scheduler.h"

class SJF_NP : public Scheduler
{
    std::vector<Process> ready;
    std::vector<Process> completed;
    std::vector<Process> all_Processes;

public:
    void add_process(const Process &P) override;
    void run(int current_time) override;
    bool has_pending() const override;
    std::vector<Process> get_completed() const override;
};

#endif
