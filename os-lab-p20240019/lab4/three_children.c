#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int i;
    pid_t pid;

    for (i = 1; i <= 3; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            /* Child process */
            printf("Child %d (PID %d): sleeping...\n", i, getpid());
            sleep(30);
            exit(0);
        }
    }

    /* Parent waits and shows tree */
    printf("Parent (PID %d): all children created\n", getpid());
    sleep(20);

    /* Wait for all children */
    for (i = 0; i < 3; i++) {
        wait(NULL);
    }
    printf("Parent: all children cleaned up\n");
    return 0;
}
