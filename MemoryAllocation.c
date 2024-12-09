#include <stdio.h>
#include <stdlib.h>

// Structure to store block information
typedef struct Block {
    int id;
    int start;
    int end;
    struct Block* next;
} Block;

// Global variables
Block* head = NULL;
int pm_size = 0; // Physical memory size
int remaining_memory = 0; // Remaining unallocated memory
int fit_algorithm = 0; // 0 = First Fit, 1 = Best Fit

// Function to print allocation table
void print_allocation() {
    printf("ID    Start   End\n");
    printf("-------------------\n");
    Block* current = head;
    while (current) {
        printf("%-5d %-7d %-7d\n", current->id, current->start, current->end);
        current = current->next;
    }
    printf("\n");
}

// Option 1: Enter parameters
void enter_parameters() {
    printf("Enter size of physical memory: ");
    scanf("%d", &pm_size);
    remaining_memory = pm_size;

    printf("Enter hole-fitting algorithm (0=first fit, 1=best_fit): ");
    scanf("%d", &fit_algorithm);

    head = NULL; // Initialize linked list with no blocks
}

// Option 2: Allocate memory for block
void allocate_memory() {
    int block_id, block_size;
    printf("Enter block id: ");
    scanf("%d", &block_id);
    printf("Enter block size: ");
    scanf("%d", &block_size);

    if (block_size > remaining_memory) {
        printf("Not enough memory to allocate block.\n");
        return;
    }

    Block* new_block = (Block*)malloc(sizeof(Block));
    new_block->id = block_id;
    new_block->next = NULL;

    Block* current = head;
    Block* prev = NULL;
    Block* best_prev = NULL;
    int best_hole_size = pm_size + 1;
    int start = 0;

    while (current) {
        int hole_size = current->start - start;

        if (hole_size >= block_size) {
            if (fit_algorithm == 0) {
                break;
            } else if (hole_size < best_hole_size) {
                best_hole_size = hole_size;
                best_prev = prev;
            }
        }

        start = current->end;
        prev = current;
        current = current->next;
    }

    if (fit_algorithm == 1 && best_prev) {
        prev = best_prev;
        current = best_prev->next;
        start = prev ? prev->end : 0;
    }

    if (pm_size - start >= block_size) {
        new_block->start = start;
        new_block->end = start + block_size;

        if (!prev) {
            new_block->next = head;
            head = new_block;
        } else {
            new_block->next = current;
            prev->next = new_block;
        }

        remaining_memory -= block_size;
        print_allocation();
    } else {
        free(new_block);
        printf("Failed to allocate block.\n");
    }
}

// Option 3: Deallocate memory for block
void deallocate_memory() {
    int block_id;
    printf("Enter block id: ");
    scanf("%d", &block_id);

    Block* current = head;
    Block* prev = NULL;

    while (current && current->id != block_id) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        printf("Block id not found.\n");
        return;
    }

    if (prev) {
        prev->next = current->next;
    } else {
        head = current->next;
    }

    remaining_memory += current->end - current->start;
    free(current);
    print_allocation();
}

// Option 4: Defragment memory
void defragment_memory() {
    Block* current = head;
    int start = 0;

    while (current) {
        int size = current->end - current->start;
        current->start = start;
        current->end = start + size;
        start = current->end;
        current = current->next;
    }

    print_allocation();
}

// Option 5: Quit program
void quit_program(Block* node) {
    if (!node) return;
    quit_program(node->next);
    free(node);
}

int main() {
    int choice;

    while (1) {
        printf("Memory allocation\n");
        printf("-----------------\n");
        printf("1) Enter parameters\n");
        printf("2) Allocate memory for block\n");
        printf("3) Deallocate memory for block\n");
        printf("4) Defragment memory\n");
        printf("5) Quit program\n\n");
        printf("Enter selection: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enter_parameters();
                break;
            case 2:
                allocate_memory();
                break;
            case 3:
                deallocate_memory();
                break;
            case 4:
                defragment_memory();
                break;
            case 5:
                quit_program(head);
                printf("Quitting program...\n");
                return 0;
            default:
                printf("Invalid selection.\n");
        }
    }

    return 0;
}
