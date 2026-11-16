#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ITERATIONS 100000

int shared_counter = 0;

void *increment_counter(void *arg) {
    long thread_id = (long)arg;

    for (int i = 0; i < ITERATIONS; i++) {
        shared_counter++;
    }

    printf("Thread %ld finished.\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    printf("Starting %d threads...\n", NUM_THREADS);

    // Create threads
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, (void *)i);
    }

    // Wait for all threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", shared_counter);
    printf("Expected counter value: %d\n", NUM_THREADS * ITERATIONS);

    return 0;
}
