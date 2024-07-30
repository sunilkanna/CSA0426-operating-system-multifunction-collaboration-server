#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

sem_t rw_mutex;   // Semaphore for writers to get exclusive access to the resource
sem_t mutex;      // Semaphore for synchronizing access to the read_count
int read_count = 0;  // Number of active readers

void* reader(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&mutex);   // Lock the mutex for updating read_count
        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_mutex);  // If this is the first reader, lock the resource
        }
        sem_post(&mutex);   // Unlock the mutex

        // Reading section
        printf("Reader %d is reading\n", id);
        sleep(1);  // Simulate reading time

        sem_wait(&mutex);   // Lock the mutex for updating read_count
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_mutex);  // If this is the last reader, unlock the resource
        }
        sem_post(&mutex);   // Unlock the mutex

        sleep(1);  // Simulate time between reads
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&rw_mutex);  // Lock the resource for writing

        // Writing section
        printf("Writer %d is writing\n", id);
        sleep(1);  // Simulate writing time

        sem_post(&rw_mutex);  // Unlock the resource

        sleep(1);  // Simulate time between writes
    }
    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];
    int reader_ids[5], writer_ids[2];

    // Initialize semaphores
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for threads to complete (they won't, in this infinite loop example)
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}

