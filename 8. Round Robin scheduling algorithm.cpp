#include <stdio.h>

typedef struct {
    int pid;          // Process ID
    int burst_time;   // Burst Time
    int remaining_time; // Remaining Burst Time
    int completion_time; // Completion Time
} Process;

void round_robin(Process processes[], int n, int time_quantum) {
    int time = 0; // Current time
    int completed = 0; // Number of processes completed

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > time_quantum) {
                    // Execute process for time_quantum time
                    time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                } else {
                    // Execute process for remaining time
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    processes[i].completion_time = time;
                    completed++;
                }

                // Print the current state
                printf("Time %d: Process %d executed\n", time, processes[i].pid);
            }
        }
    }
}

int main() {
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    round_robin(processes, n, time_quantum);

    printf("\nProcess Completion Times:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: %d\n", processes[i].pid, processes[i].completion_time);
    }

    return 0;
}
