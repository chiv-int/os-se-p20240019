/* zombie.c - parent calls wait() to clean up zombie */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        /* Child — exits immediately */
        printf("Child (PID %d): exiting now.\n", getpid());
        exit(0);
    }

    /* Parent — sleeps 10 seconds then calls wait() */
    printf("Parent (PID %d): sleeping 10 seconds before wait()...\n", getpid());
    sleep(10);
    wait(NULL);
    printf("Parent: wait() called, zombie cleaned up!\n");
    return 0;
}
