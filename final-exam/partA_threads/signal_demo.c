#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t keep_running = 1;

void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("\nCaught SIGINT (interactive interrupt). Cleaning up...\n");
    } else if (sig == SIGTERM) {
        printf("\nCaught SIGTERM (termination request). Cleaning up...\n");
    }
    keep_running = 0;
}

int main() {
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    printf("signal_demo running (PID=%d). Waiting for SIGINT (Ctrl+C) or SIGTERM...\n", getpid());

    while (keep_running) {
        printf("Looping... still alive\n");
        sleep(2);
    }

    printf("Cleanup complete. Exiting gracefully.\n");
    return 0;
}
