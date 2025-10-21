#ifndef PROCESS_H
#define PROCESS_H
#include<iostream>
using namespace std;

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
    bool is_finished(){
        if(remaining_time == 0) return true;
        else return false;
    }
    void print_data_of_process();
};
#endif
