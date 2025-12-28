# CPU Process Scheduler Simulator (C++)
## Overview

This project simulates classic **CPU scheduling algorithms** using **Object-Oriented Programming in C++**.
It models real OS behavior such as **process arrival times**, **preemption**, and **time slicing**, and produces both **performance metrics** and **Gantt charts**.

The design emphasizes **polymorphism, clean separation of concerns, and correctness**.

---

## Implemented Scheduling Algorithms

* **FCFS** — First Come First Serve
* **SJF (Non-Preemptive)**
* **SJF (Preemptive / SRTF)**
* **Priority Scheduling (Non-Preemptive)**
* **Round Robin** (configurable time quantum)

All algorithms handle **dynamic process arrival**.

---

## Key Features

* Object-oriented design with an abstract `Scheduler` base class
* Runtime polymorphism for algorithm switching
* Accurate **Gantt chart generation**
* Calculation of:
  * Average Waiting Time
  * Average Turnaround Time
  * Average Response Time
* Single input source for fair comparison
* Refactored, reusable arrival-handling logic

---

## Project Structure

```
.
├── main.cpp
├── process.h / process.cpp
├── scheduler.h
├── simulation.h / simulation.cpp
├── fcfs.h / fcfs.cpp
├── sjf_np.h / sjf_np.cpp
├── sjf_p.h / sjf_p.cpp
├── priority.h / priority.cpp
├── round_robin.h / round_robin.cpp
└── README.md
```

---

## Core Design

* **Process**
  Holds process attributes and runtime data.

* **Scheduler (abstract base class)**
  Defines a common interface for all schedulers.

* **Concrete Schedulers**
  Implement algorithm-specific logic.

* **Simulation**
  Runs a scheduler, computes metrics, prints Gantt charts.

Schedulers own their process copies; `Simulation` only reads results.

---

## Gantt Chart

Each scheduler records execution slices internally.
The simulation merges and prints them as a readable timeline.

Example (Round Robin):

```
| P1 | P2 | P3 | P1 |
0    2    4    6    8
```

---

## How to Build & Run

Compile using:

```bash
g++ -std=c++17 *.cpp -o scheduler_sim
```

Run:

```bash
./scheduler_sim
```

(Processes are currently defined in `main.cpp`.)

---

## Learning Outcomes

* Practical understanding of CPU scheduling
* Correct use of OOP and polymorphism in C++
* Handling preemption and time-based simulation
* Writing clean, refactorable systems code

---

## Future Extensions

* File / CLI-based input
* Preemptive priority scheduling
* Export results to file
* Automated test cases

---

## Author

Built entirely by the student as a learning-focused systems project.

---
