#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

void *worker(void *arg) {
    long thread_id = (long)arg;

    printf("Worker thread %ld is running...\n", thread_id);
    sleep(60);

    printf("Worker thread %ld finished.\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    printf("Main process PID: %d\n", getpid());

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, worker, (void *)i);
    }

    printf("Created %d worker threads.\n", NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished.\n");

    return 0;
}
