Specification:
The program simulates resource allocation to requesting processes and demonstrates deadlock
avoidance with the Banker's algorithm. A menu controls the operations, and each choice calls
the appropriate procedure, where the choices are:
1) Enter parameters
2) Run the Banker's algorithm to determine a safe sequence
3) Quit program and free memory

Requirements:
• The program uses a claim graph consisting of processes, multi-unit resources, request edges,
allocation edges, and claim edges to represent the state of allocated resources to processes.
• The graph can be represented by a set of arrays/vectors:
  o Resource vector: an m-element vector, where m is the number of resources and each
  entry resource[j] records the total number of units of resource j.
  o Available vector: an m-element vector, where m is the number of resources and each
  entry available[j] records the number of units of resource j that are available.
  o Max claims array: an nxm-element array, where m is the number of resources and n is
  the number of processes, and each entry maxclaim[i][j] contains an integer that
  records the maximum number of units of resource j that process i may ever request.
  o Allocation array: an nxm-element array, where m is the number of resources and n is
  the number of processes, and each entry allocation[i][j] contains an integer that
  records the number of units of resource j that process i has actually been allocated.
  o Need array: an nxm array, where m is the number of resources and n is the number of
  processes, and each entry need[i][j] contains an integer that records the number of
  units of resource j that process i may need in the future.
