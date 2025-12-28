#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>

class Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int start_time = -1;
    int completion_time = -1;

public:
    Process(int PID, int arrival, int burst, int priority);
    bool is_finished()
    {
        if (remaining_time == 0)
            return true;
    }

    int get_pid() const { return pid; }
    int get_arrival_time() const { return arrival_time; }
    int get_burst_time() const { return burst_time; }
    int get_priority() const { return priority; }

    int get_remaining_time() const { return remaining_time; }
    void set_remaining_time(int r) { remaining_time = r; }

    int get_start_time() const { return start_time; }
    void set_start_time(int t)
    {
        if (start_time == -1)
            start_time = t;
    }

    int get_completion_time() const { return completion_time; }
    void set_completion_time(int t) { completion_time = t; }

    bool is_finished() const { return remaining_time == 0; }

    void print_data_of_process();
};
#endif
