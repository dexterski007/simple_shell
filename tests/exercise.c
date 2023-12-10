#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(void)
{
    char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
    int i, status;

    printf("Before execve\n");

    for (i = 0; i < 5; i++)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("Error in fork:");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            // This is the child process
            execve(argv[0], argv, NULL);
            perror("Error in execve:"); // This line will be reached only if execve fails
            exit(EXIT_FAILURE);
        }
        else
        {
            // This is the parent process
            sleep(2);
            wait(&status);
            printf("After execve round %d and status is: %d\n", (i + 1), status);
        }
    }

    return (0);
}
