#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

// Function to display the shell prompt
void display_prompt() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("NaeemShell:- %s$ ", cwd); // Changed prompt to NaeemShell
    } else {
        perror("getcwd() error");
    }
}

// Function to execute a command
void execute_command(char **args) {
    pid_t pid = fork();
    if (pid < 0) {
        // Error forking
        perror("Fork failed");
    } else if (pid == 0) {
        // Child process: execute command
        if (execvp(args[0], args) == -1) {
            perror("Execution failed");
        }
        exit(EXIT_FAILURE); // Exit if exec fails
    } else {
        // Parent process: wait for child
        wait(NULL);
    }
}

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *args[100];
    char *token;
    int i;

    while (1) {
        display_prompt(); // Show the prompt

        // Read the command from user
        nread = getline(&line, &len, stdin);
        if (nread == -1) {
            // Exit on <CTRL+D>
            printf("\nExiting NaeemShell.\n");
            break;
        }

        // Tokenize the input
        i = 0;
        token = strtok(line, " \n");
        while (token != NULL && i < 100) {
            args[i++] = token;
            token = strtok(NULL, " \n");
        }
        args[i] = NULL; // Null-terminate the array

        // Ignore empty input
        if (args[0] == NULL) {
            continue;
        }

        // Execute the command
        execute_command(args);
    }

    free(line); // Free allocated memory
    return 0;
}
