#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 256

int main(void) {
    char *line = NULL;
    size_t len = 0;

    while (1) {
        // Print the prompt
        printf("$ ");
        fflush(stdout); // Flush the output buffer to ensure the prompt is displayed

        // Read the command from the user
        ssize_t read = getline(&line, &len, stdin);

        // Check for errors or end-of-file
        if (read == -1) {
            perror("Error reading command");
            break;
        }

        // Remove the newline character at the end
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }

        // Parse the command and its arguments
        char *args[MAX_LINE_LENGTH];
        args[0] = strtok(line, " ");
        for (int i = 1; i < MAX_LINE_LENGTH; i++) {
            args[i] = strtok(NULL, " ");
            if (args[i] == NULL) {
                break;
            }
        }

        // Execute the command in a child process
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("Error in fork:");
            break;
        }

        if (child_pid == 0) {
            // This is the child process
            execvp(args[0], args);

            // If execvp fails, print an error message
            perror("Error executing command");
            _exit(EXIT_FAILURE);
        } else {
            // This is the parent process
            // Wait for the child process to complete
            wait(NULL);
        }
    }

    // Free the allocated memory
    free(line);

    return 0;
}
