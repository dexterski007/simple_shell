#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t child_pid;
    int status;

    child_pid = fork();

    if (child_pid == -1) {
        perror("Error:");
        return 1;
    }

    if (child_pid == 0) {
        printf("Child process: My pid is %u\n", getpid());
        // Child process work...
        exit(42);  // Exit with a status of 42
    } else {
        // Parent process
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process did not exit normally\n");
        }
    }

    return 0;
}