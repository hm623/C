Specification:
The program simulates memory allocation with a chosen hole-fitting algorithm (First-fit,
Best-fit) and implements deallocation and defragmentation. A menu controls the
operations, and each choice calls the appropriate procedure, where the choices are:
1) Enter parameters
2) Allocate memory for a block
3) Deallocate memory for a block
4) Defragment memory
5) Quit program and free memory

Requirements:
• The size of physical memory is represented by an integer pm_size.
• The allocated blocks are contained within a linked list, where each allocated block is
a structure containing: (1) the id, (2) the starting address of the block, (3) the ending
address of the block, and (4) a link to the next allocated block.
• Each allocation request prompts for: (1) the id and (2) the size of the new block. If the
id is a duplicate and/or the remaining physical memory is not enough to fit the
request, the request is rejected, and an appropriate message is displayed.
• Each deallocation request prompts for the id. If the id is invalid, the request is
rejected.
• Defragmentation compacts the blocks to be contiguous, and coalesces the holes into
one hole at the far--right end (highest memory addresses) of physical memory.
