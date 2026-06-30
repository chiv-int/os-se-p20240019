#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

void *worker(void *arg) {
    long id = (long)arg;
    int result = (id + 1) * (id + 1);
    printf("Thread %ld (tid=%lu): computed value = %d\n", id, pthread_self(), result);
    sleep(4);
    int *ret = malloc(sizeof(int));
    *ret = result;
    pthread_exit(ret);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int sum = 0;

    for (long i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, worker, (void *)i) != 0) {
            perror("pthread_create failed");
            exit(1);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        void *res;
        pthread_join(threads[i], &res);
        int val = *(int *)res;
        printf("Joined thread %d, result = %d\n", i, val);
        sum += val;
        free(res);
    }

    printf("Summary: all %d workers joined. Total = %d\n", NUM_THREADS, sum);

    // CURVEBALL: spawn 2 extra workers AFTER originals have joined
    printf("Original threads joined. Spawning 2 extra workers...\n");
    pthread_t extra_threads[2];
    for (long i = 0; i < 2; i++) {
        pthread_create(&extra_threads[i], NULL, worker, (void *)(NUM_THREADS + i));
    }
    sleep(2); // window to capture LWPs while extras are alive
    for (int i = 0; i < 2; i++) {
        void *res;
        pthread_join(extra_threads[i], &res);
        printf("Joined extra thread %d, result = %d\n", i, *(int *)res);
        free(res);
    }
    printf("Extra workers joined and exited.\n");

    return 0;
}

