#include <stdio.h>
#include <string.h>

extern char **environ;

char *_getenv(const char *name) {
    // Iterate through the environment variables
    for (int i = 0; environ[i] != NULL; i++) {
        // Find the position of the '=' character
        char *equal_sign = strchr(environ[i], '=');

        // Check if the current environment variable matches the specified name
        if (equal_sign != NULL && equal_sign - environ[i] == strlen(name) && strncmp(environ[i], name, equal_sign - environ[i]) == 0) {
            // If yes, return the value part of the environment variable
            return equal_sign + 1; // Skip the '=' character
        }
    }

    // Environment variable not found
    return NULL;
}

int main(void) {
    // Example usage of _getenv
    const char *variable_name = "PATH";
    char *variable_value = _getenv(variable_name);

    if (variable_value != NULL) {
        printf("%s: %s\n", variable_name, variable_value);
    } else {
        printf("%s environment variable not found\n", variable_name);
    }

    return 0;
}
