#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ITERATIONS 100000

int shared_counter = 0;

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment_counter(void *arg) {
    long thread_id = (long)arg;

    for (int i = 0; i < ITERATIONS; i++) {
        pthread_mutex_lock(&counter_mutex);

        shared_counter++;

        pthread_mutex_unlock(&counter_mutex);
    }

    printf("Thread %ld finished.\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    printf("Starting %d threads...\n", NUM_THREADS);

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, (void *)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", shared_counter);
    printf("Expected counter value: %d\n", NUM_THREADS * ITERATIONS);

    pthread_mutex_destroy(&counter_mutex);

    return 0;
}
