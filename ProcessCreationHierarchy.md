Specification:
The program creates/destroys child processes based on choosing from a menu of choices, where each
choice calls the appropriate procedure, where the choices are:
1) Enter parameters
2) Create a new child process
3) Destroy all descendants of a process
4) Quit program and free memory

Requirements
- Create a process creation hierarchy as a dynamic array of length n which references the process
control blocks (PCBs), indexed 0 to n-1
- Each PCB is a structure consisting of two fields:
 o parent: a PCB index corresponding to the process’ creator
 o children: a pointer to a linked list, where each node contains the PCB index of one child
 process and a link to the next child in the list
- The necessary functions are simplified as follows:
 o create() represents the create function, which prompts for the parent process PCB[p]. The
function creates a new child process PCB[q] of process PCB[p] by performing the following
tasks:
    + allocate a free PCB[q]
    + record the parent's index, p, in PCB[q]
    + initialize the list of children of PCB[q] as empty (NULL)
    + create a new link containing the child's index q and append the link to the linked list
    of PCB[p]
 o destroy() represents the destroy function, which prompts for the parent process PCB[p]. The
   function recursively destroys all descendent processes (child, grandchild, etc.) of process
   PCB[p] by performing the following tasks: for each element q on the linked list of children of
   PCB[p]:
   + destroy(q) /* recursively destroy all descendants */
   + free PCB[q]
   + deallocate the element q from the linked list
