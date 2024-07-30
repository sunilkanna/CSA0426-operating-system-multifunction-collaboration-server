#include <stdio.h>

#include <stdbool.h>



#define P 5 // Number of processes

#define R 3 // Number of resources



// Function to check system safety

bool is_safe(int processes[], int avail[], int max[][R], int allot[][R]) {

    int need[P][R], work[R];

    bool finish[P] = {0};



    // Calculate need matrix

    for (int i = 0; i < P; i++)

        for (int j = 0; j < R; j++)

            need[i][j] = max[i][j] - allot[i][j];



    // Initialize work with available resources

    for (int i = 0; i < R; i++)

        work[i] = avail[i];



    // Check for safe state

    for (int count = 0; count < P;) {

        bool found = false;

        for (int p = 0; p < P; p++) {

            if (!finish[p]) {

                int j;

                for (j = 0; j < R; j++)

                    if (need[p][j] > work[j])

                        break;

                if (j == R) {

                    for (int k = 0; k < R; k++)

                        work[k] += allot[p][k];

                    finish[p] = true;

                    found = true;

                    count++;

                }

            }

        }

        if (!found)

            return false;

    }

    return true;

}



int main() {

    int processes[P] = {0, 1, 2, 3, 4};

    int avail[R] = {3, 3, 2};

    int max[P][R] = {

        {7, 5, 3},

        {3, 2, 2},

        {9, 0, 2},

        {2, 2, 2},

        {4, 3, 3}

    };

    int allot[P][R] = {

        {0, 1, 0},

        {2, 0, 0},

        {3, 0, 2},

        {2, 1, 1},

        {0, 0, 2}

    };



    if (is_safe(processes, avail, max, allot))

        printf("The system is in a safe state.\n");

    else

        printf("The system is not in a safe state.\n");



    return 0;

}

