Specification:
The program mimics the execution of different processes under different scheduling algorithms.
The simulation maintains a table that reflects the current state of the system, based on choosing
from a menu of choices, where each choice calls the appropriate procedure, where the choices
are:
1) Enter parameters
2) Schedule processes with FIFO algorithm
3) Schedule processes with SJF algorithm (non-preemptive)
4) Schedule processes with SRT algorithm (preemptive version of SJF)
5) Quit program and free memory

Requirements:
• Create a table to record the status of different processes based on the following parameters:
  o id: the unique identifier of the process
  o arrival: the point in time when the process enters the ready list to be executed by the
  CPU
  o total_cpu: the amount of CPU time the process will consume between arrival and
  departure
  o total_remaining: the amount of CPU time remaining for a process to complete {used
  for SRT scheduling only}
  o done: a flag that indicates whether the process has been successfully completed (1) or
  not (0)
  o start_time: the time when the process has begun being executed by the CPU
  o already_started: a flag that indicated whether the process has already begun (1) or
  not (0) {used for SRT scheduling only}
  o end_time: the time when the process has been completed by the CPU
  o turnaround_time: the sum of the total CPU time and the waiting time (alternatively:
  the difference between the end time and the arrival time)
• Calculate the values for the start_time, end_time, and turnaround_time for each process
based on the selected scheduling algorithm.
