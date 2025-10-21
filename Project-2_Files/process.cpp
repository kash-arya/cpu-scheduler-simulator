#include "process.h"
#include <iostream>

Process::Process(int PID, int arrival, int burst, int priority){
    pid = PID;
    arrival_time = arrival;
    burst_time = burst;
    this->priority = priority;
    remaining_time = burst;
}

void Process::print_data_of_process()
{
    cout << "\nPID: " << pid
         << "\nArrival Time: " << arrival_time
         << "\nBurst Time: " << burst_time
         << "\nPriority: " << priority
         << "\nRemaining Time: " << remaining_time
         << "\nStart Time: " << start_time
         << "\nCompletion Time: " << completion_time;
}
