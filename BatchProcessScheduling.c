#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int arrival;
    int total_cpu;
    int total_remaining;
    int done;
    int start_time;
    int end_time;
    int turnaround_time;
} Process;

Process *table = NULL;  // Array of processes
int total_processes = 0;

// Function to print the table of processes
void print_table() {
    printf("\nID\tArrival\tTotal\tStart\tEnd\tTurnaround\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < total_processes; i++) {
        printf("%d\t%d\t%d", table[i].id, table[i].arrival, table[i].total_cpu);
        if (table[i].done) {
            printf("\t%d\t%d\t%d", table[i].start_time, table[i].end_time, table[i].turnaround_time);
        }
        printf("\n");
    }
}

// Function to enter process parameters (Option 1)
void enter_parameters() {
    printf("Enter total number of processes: ");
    scanf("%d", &total_processes);

    // Allocate memory for the processes
    table = (Process *)malloc(total_processes * sizeof(Process));

    // Get details for each process
    for (int i = 0; i < total_processes; i++) {
        printf("\nEnter process ID: ");
        scanf("%d", &table[i].id);
        printf("Enter arrival time for process P[%d]: ", table[i].id);
        scanf("%d", &table[i].arrival);
        printf("Enter total cycles for process P[%d]: ", table[i].id);
        scanf("%d", &table[i].total_cpu);

        // Initialize values
        table[i].total_remaining = table[i].total_cpu;
        table[i].done = 0;
        table[i].start_time = -1;  
    }

    print_table();
}

// Function to schedule processes using FIFO (Option 2)
void fifo_scheduling() {
    int current_time = 0;

    for (int i = 0; i < total_processes; i++) {
        table[i].done = 0;
    }

    for (int i = 0; i < total_processes; i++) {
        if (current_time < table[i].arrival) {
            current_time = table[i].arrival;
        }

        table[i].start_time = current_time;
        table[i].end_time = current_time + table[i].total_cpu;
        table[i].turnaround_time = table[i].end_time - table[i].arrival;
        table[i].done = 1;

        current_time = table[i].end_time;
    }

    print_table();
}

// Function to schedule processes using SJF (Option 3)
void sjf_scheduling() {
    int current_time = 0, processes_done = 0;

    for (int i = 0; i < total_processes; i++) {
        table[i].done = 0;
    }

    while (processes_done < total_processes) {
        int min_cpu = 9999, selected_index = -1;

        for (int i = 0; i < total_processes; i++) {
            if (!table[i].done && table[i].arrival <= current_time && table[i].total_cpu < min_cpu) {
                min_cpu = table[i].total_cpu;
                selected_index = i;
            }
        }

        if (selected_index != -1) {
            table[selected_index].start_time = current_time;
            table[selected_index].end_time = current_time + table[selected_index].total_cpu;
            table[selected_index].turnaround_time = table[selected_index].end_time - table[selected_index].arrival;
            table[selected_index].done = 1;
            current_time = table[selected_index].end_time;
            processes_done++;
        } else {
            current_time++;
        }
    }

    print_table();
}

// Function to schedule processes using SRT (Option 4)
void srt_scheduling() {
    int current_time = 0, processes_done = 0;

    for (int i = 0; i < total_processes; i++) {
        table[i].done = 0;
        table[i].total_remaining = table[i].total_cpu;
        table[i].start_time = -1;
    }

    while (processes_done < total_processes) {
        int min_remaining = 9999, selected_index = -1;

        for (int i = 0; i < total_processes; i++) {
            if (!table[i].done && table[i].arrival <= current_time && table[i].total_remaining < min_remaining) {
                min_remaining = table[i].total_remaining;
                selected_index = i;
            }
        }

        if (selected_index != -1) {
            if (table[selected_index].start_time == -1) {
                table[selected_index].start_time = current_time;
            }

            table[selected_index].total_remaining--;
            current_time++;

            if (table[selected_index].total_remaining == 0) {
                table[selected_index].end_time = current_time;
                table[selected_index].turnaround_time = table[selected_index].end_time - table[selected_index].arrival;
                table[selected_index].done = 1;
                processes_done++;
            }
        } else {
            current_time++;
        }
    }

    print_table();
}

// Function to quit and free memory (Option 5)
void quit_program() {
    if (table != NULL) {
        free(table);
    }
    printf("Quitting program...\n");
}

// Main function
int main() {
    int choice = 0;

    while (choice != 5) {
        printf("\nBatch scheduling\n");
        printf("----------------\n");
        printf("1) Enter parameters\n");
        printf("2) Schedule processes with FIFO algorithm\n");
        printf("3) Schedule processes with SJF algorithm\n");
        printf("4) Schedule processes with SRT algorithm\n");
        printf("5) Quit and free memory\n");
        printf("Enter selection: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enter_parameters();
                break;
            case 2:
                fifo_scheduling();
                break;
            case 3:
                sjf_scheduling();
                break;
            case 4:
                srt_scheduling();
                break;
            case 5:
                quit_program();
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
