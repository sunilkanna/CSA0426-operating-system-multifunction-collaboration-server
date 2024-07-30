#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;  // Number of items in the buffer
sem_t empty;    // Semaphore to track empty slots in the buffer
sem_t full;     // Semaphore to track filled slots in the buffer
pthread_mutex_t mutex;  // Mutex to protect buffer access

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100;  // Produce a random item
        sem_wait(&empty);     // Wait for an empty slot
        pthread_mutex_lock(&mutex);  // Lock the buffer
        
        buffer[count] = item;
        count++;
        printf("Produced: %d\n", item);
        
        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&full);     // Signal that there's a filled slot
        
        sleep(1);  // Sleep for a while to simulate production time
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);      // Wait for a filled slot
        pthread_mutex_lock(&mutex);  // Lock the buffer
        
        count--;
        item = buffer[count];
        printf("Consumed: %d\n", item);
        
        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&empty);     // Signal that there's an empty slot
        
        sleep(1);  // Sleep for a while to simulate consumption time
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize the semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create the producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for the threads to finish (they won't, in this infinite loop example)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

