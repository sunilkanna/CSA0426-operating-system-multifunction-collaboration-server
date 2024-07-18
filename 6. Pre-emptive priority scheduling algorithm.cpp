#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
struct Process {
    int pid;            // Process ID
    int bt;            // Burst time
    int priority;        // Priority (lower value = higher priority)
    int at;             // Arrival time
    int rt;             // Remaining time
};

// Function to swap two processes
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort processes based on arrival time
void sort_by_arrival_time(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].at > proc[j + 1].at) {
                swap(&proc[j], &proc[j + 1]);
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        printf("Enter burst time, priority, and arrival time for process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].bt, &proc[i].priority, &proc[i].at);
        proc[i].pid = i + 1;
        proc[i].rt = proc[i].bt;
    }

    sort_by_arrival_time(proc, n);

    int completed = 0, current_time = 0;
    int wt[n], tat[n];

    while (completed != n) {
        int highest_priority = 9999, shortest_job = 9999, index = -1;

        // Find the highest priority process that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].at <= current_time && proc[i].rt < shortest_job && proc[i].rt > 0) {
                shortest_job = proc[i].rt;
                highest_priority = proc[i].priority;
                index = i;
            }
        }

        if (index == -1) {
            current_time++;
        } else {
            proc[index].rt--;

            if (proc[index].rt == 0) {
                completed++;

                wt[index] = current_time + 1 - proc[index].bt - proc[index].at;
                tat[index] = current_time + 1 - proc[index].at;
            }

            current_time++;
        }
    }

    // Calculate and print average waiting time and turnaround time

    return 0;
}
