#include <stdio.h>
#include <stdlib.h>

// Define a node in the linked list
typedef struct Node {
    int process_index;
    struct Node *next;
} Node;

// Define the Process Control Block (PCB)
typedef struct PCB {
    int parent;
    Node *children;
} PCB;

// Global variable for the dynamic array of PCBs
PCB *pcb_array = NULL;
int max_processes = 0;

// Function to print the hierarchy of processes without printing "None"
void print_hierarchy() {
    for (int i = 0; i < max_processes; i++) {
        if (pcb_array[i].parent != -1 && pcb_array[i].children != NULL) {
            printf("PCB[%d] is the parent of: ", i);
            Node *child = pcb_array[i].children;
            while (child != NULL) {
                printf("PCB[%d] ", child->process_index);
                child = child->next;
            }
            printf("\n");
        }
    }
}

// Procedure for Option #1: Enter Parameters
void enter_parameters() {
    printf("Enter maximum number of processes: ");
    scanf("%d", &max_processes);

    pcb_array = (PCB *)malloc(max_processes * sizeof(PCB));

    // Initialize the parent of all PCBs to -1 and children to NULL
    for (int i = 0; i < max_processes; i++) {
        pcb_array[i].parent = -1;
        pcb_array[i].children = NULL;
    }

    // Set PCB[0] as the root process (no parent)
    pcb_array[0].parent = 0;
}

// Procedure for Option #2: Create a New Child Process
void create_child() {
    int p, q;
    printf("Enter the parent process index: ");
    scanf("%d", &p);

    if (pcb_array[p].parent == -1) {
        printf("Parent process does not exist.\n");
        return;
    }

    // Find the first available PCB (index without a parent)
    for (q = 0; q < max_processes; q++) {
        if (pcb_array[q].parent == -1) {
            break;
        }
    }

    if (q == max_processes) {
        printf("No more available PCBs.\n");
        return;
    }

    // Allocate new child process
    pcb_array[q].parent = p;
    pcb_array[q].children = NULL;

    // Create a new linked list node for the child
    Node *new_child = (Node *)malloc(sizeof(Node));
    new_child->process_index = q;
    new_child->next = NULL;

    // Append the new child to the end of the linked list of PCB[p]
    if (pcb_array[p].children == NULL) {
        pcb_array[p].children = new_child;  // If there are no children, set this as the first child
    } else {
        Node *temp = pcb_array[p].children;
        while (temp->next != NULL) {
            temp = temp->next;  // Traverse to the last child
        }
        temp->next = new_child;  // Append new child at the end
    }

    // Print the updated hierarchy in the required format
    print_hierarchy();
}

// Recursive procedure to destroy children processes
void destroy_descendants(int p) {
    Node *child = pcb_array[p].children;

    while (child != NULL) {
        int q = child->process_index;

        // Recursively destroy descendants of child
        destroy_descendants(q);

        // Free child node memory
        Node *temp = child;
        child = child->next;
        free(temp);

        // Reset PCB[q]
        pcb_array[q].parent = -1;
        pcb_array[q].children = NULL;
    }

    pcb_array[p].children = NULL;
}

// Procedure for Option #3: Destroy All Descendants
void destroy_children() {
    int p;
    printf("Enter the index of the process whose descendants are to be destroyed: ");
    scanf("%d", &p);

    if (pcb_array[p].parent == -1) {
        printf("Process does not exist.\n");
        return;
    }

    // Recursively destroy descendants of process p
    destroy_descendants(p);
}

// Procedure for Option #4: Quit Program and Free Memory
void quit_program() {
    if (pcb_array != NULL) {
        destroy_descendants(0); // Destroy all descendants of the root process
        free(pcb_array);
        pcb_array = NULL;
    }
    printf("Quitting program...\n");
}

// Function to display the menu
void display_menu() {
    printf("Process creation and destruction\n");
    printf("--------------------------------\n");
    printf("1) Enter parameters\n");
    printf("2) Create a new child process\n");
    printf("3) Destroy all descendants of a process\n");
    printf("4) Quit program and free memory\n");
    printf("Enter selection: ");
}

// Main function
int main() {
    int choice;

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enter_parameters();
                break;
            case 2:
                create_child();
                break;
            case 3:
                destroy_children();
                break;
            case 4:
                quit_program();
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
