**CPU Scheduling Simulator (C++)**
A C++ simulator for classic CPU scheduling algorithms, built using OOP and runtime polymorphism.

**Algorithms Implemented**
1. FCFS
2. SJF (Non-Preemptive)
3. SJF (Preemptive / SRTF)
4. Priority Scheduling
5. Round Robin (configurable quantum)

**Features**
1. Dynamic process arrivals
2. Accurate Gantt chart generation
3. Average Waiting, Turnaround, and Response time calculation
4. Clean object-oriented design

**Build & Run**
g++ -std=c++17 *.cpp -o scheduler_sim
./scheduler_sim

**Design Highlights**
1. Abstract Scheduler base class
2. Polymorphic algorithm execution
3. Shared arrival-handling logic
4. Clear separation between scheduling and metrics

**Output Example**
| P1 | P2 | P3 | P1 |
0    2    4    6    8

**Purpose**
Academic project to understand OS scheduling and systems-level design in C++.
