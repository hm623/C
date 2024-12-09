#include <stdio.h>
#include <stdlib.h>

// Declare dynamic arrays and global variables
int *resources, *available, **max_claim, **allocated, **need;
int num_processes, num_resources;

/***********************************************************/
void print_resource_vector() {
    // Print total units and available units of each resource
    printf("\n        Units   Available\n");
    printf("------------------------\n");
    for (int j = 0; j < num_resources; j++) {
        printf("r%d      %d      %d\n", j, resources[j], available[j]);
    }
    printf("\n");
}

/***************************************************************/
void print_matrix() {
    // Print the max claim, allocated, and need matrices
    printf("\n        Max claim                       Current                         Potential\n");
    printf("        r0      r1      r2              r0      r1      r2              r0      r1      r2\n");
    printf("------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < num_processes; i++) {
        printf("p%d      ", i);
        for (int j = 0; j < num_resources; j++) {
            printf("%d       ", max_claim[i][j]);
        }
        printf("          ");
        for (int j = 0; j < num_resources; j++) {
            printf("%d       ", allocated[i][j]);
        }
        printf("          ");
        for (int j = 0; j < num_resources; j++) {
            printf("%d       ", need[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/****************************************************************/
void enter_parameters() {
    // Prompt for the number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    // Allocate memory for vectors and matrices
    resources = (int *)malloc(num_resources * sizeof(int));
    available = (int *)malloc(num_resources * sizeof(int));
    max_claim = (int **)malloc(num_processes * sizeof(int *));
    allocated = (int **)malloc(num_processes * sizeof(int *));
    need = (int **)malloc(num_processes * sizeof(int *));
    for (int i = 0; i < num_processes; i++) {
        max_claim[i] = (int *)malloc(num_resources * sizeof(int));
        allocated[i] = (int *)malloc(num_resources * sizeof(int));
        need[i] = (int *)malloc(num_resources * sizeof(int));
    }

    // Prompt for the total units of each resource
    printf("Enter number of units for resources (r0 to r%d): ", num_resources - 1);
    for (int j = 0; j < num_resources; j++) {
        scanf("%d", &resources[j]);
        available[j] = resources[j];  // Initially, all resources are available
    }

    // Prompt for the maximum claim of each process
    for (int i = 0; i < num_processes; i++) {
        printf("Enter maximum number of units process p%d will request from each resource (r0 to r%d) ", i, num_resources - 1);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &max_claim[i][j]);
            need[i][j] = max_claim[i][j];  // Initially, need is equal to max_claim
        }
    }

    // Prompt for the allocated resources of each process
    for (int i = 0; i < num_processes; i++) {
        printf("Enter number of units of each resource (r0 to r%d) allocated to process p%d: ", num_resources - 1, i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocated[i][j]);
            available[j] -= allocated[i][j];  // Update available resources
            need[i][j] -= allocated[i][j];    // Update need based on allocation
        }
    }

    // Print the vectors and matrices
    print_resource_vector();
    print_matrix();
}

/********************************************************************/
void determine_safe_sequence() {
    int *work = (int *)malloc(num_resources * sizeof(int));
    int *finish = (int *)calloc(num_processes, sizeof(int));
    int num_sequenced = 0;
    int found;

    // Initialize work vector to available vector
    for (int j = 0; j < num_resources; j++) {
        work[j] = available[j];
    }

    // Check for a safe sequence
    printf("\n");
    while (num_sequenced < num_processes) {
        found = 0;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                int can_allocate = 1;
                for (int j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }
                if (can_allocate) {
                    printf("Checking: < ");
                    for (int j = 0; j < num_resources; j++) {
                        printf("%d ", need[i][j]);
                    }
                    printf("> <= < ");
                    for (int j = 0; j < num_resources; j++) {
                        printf("%d ", work[j]);
                    }
                    printf("> :p%d safely sequenced\n", i);

                    for (int j = 0; j < num_resources; j++) {
                        work[j] += allocated[i][j];
                    }
                    finish[i] = 1;
                    num_sequenced++;
                    found = 1;
                } else {
                    printf("Checking: < ");
                    for (int j = 0; j < num_resources; j++) {
                        printf("%d ", need[i][j]);
                    }
                    printf("> <= < ");
                    for (int j = 0; j < num_resources; j++) {
                        printf("%d ", work[j]);
                    }
                    printf("> :p%d could not be sequenced\n", i);
                }
            }
        }
        if (!found) {
            printf("No safe sequence found!\n");
            break;
        }
    }

    // Free allocated memory
    free(work);
    free(finish);
}

/********************************************************************/
void quit_program() {
    // Free all dynamically allocated memory
    if (resources) free(resources);
    if (available) free(available);
    if (max_claim) {
        for (int i = 0; i < num_processes; i++) free(max_claim[i]);
        free(max_claim);
    }
    if (allocated) {
        for (int i = 0; i < num_processes; i++) free(allocated[i]);
        free(allocated);
    }
    if (need) {
        for (int i = 0; i < num_processes; i++) free(need[i]);
        free(need);
    }
    printf("Quitting program...\n");
}

/****************************************************************/
int main() {
    int choice;

    // Main menu loop
    while (1) {
        printf("\nBanker's Algorithm\n");
        printf("------------------\n");
        printf("1) Enter parameters\n");
        printf("2) Determine safe sequence\n");
        printf("3) Quit program\n");
        printf("\nEnter selection: ");
        scanf("%d", &choice);

        if (choice == 1) {
            enter_parameters();
        } else if (choice == 2) {
            determine_safe_sequence();
        } else if (choice == 3) {
            quit_program();
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
