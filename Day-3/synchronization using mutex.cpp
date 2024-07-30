#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5
#define NUM_INCREMENTS 1000

int counter = 0;  // Shared resource
pthread_mutex_t counter_mutex;  // Mutex lock for synchronizing access to counter

void* increment_counter(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        pthread_mutex_lock(&counter_mutex);  // Lock the mutex
        counter++;  // Critical section: increment the counter
        pthread_mutex_unlock(&counter_mutex);  // Unlock the mutex
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int rc;

    // Initialize the mutex
    pthread_mutex_init(&counter_mutex, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        rc = pthread_create(&threads[i], NULL, increment_counter, &thread_ids[i]);
        if (rc) {
            printf("Error: Unable to create thread %d\n", rc);
            exit(-1);
        }
    }

    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&counter_mutex);

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);

    return 0;
}

