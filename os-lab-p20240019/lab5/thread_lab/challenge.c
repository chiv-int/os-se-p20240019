#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

volatile int keep_running = 1;

void sig_handler(int signo) {
    if (signo == SIGINT) {
        printf("\n[Signal Caught] SIGINT received. Shutting down threads...\n");
        keep_running = 0;
    }
}

void *worker(void *arg) {
    int id = *(int *)arg;
    while (keep_running) {
        printf("[Thread %d] Running... (TID: %lu)\n", id, pthread_self());
        sleep(1);
    }
    printf("[Thread %d] Exiting cleanly.\n", id);
    pthread_exit(NULL);
}

int main() {
    // Register SIGINT handler
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        printf("Cannot catch SIGINT\n");
    }

    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    // Spawn two worker threads
    pthread_create(&t1, NULL, worker, &id1);
    pthread_create(&t2, NULL, worker, &id2);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("All threads cleanly exited. Goodbye.\n");
    return 0;
}