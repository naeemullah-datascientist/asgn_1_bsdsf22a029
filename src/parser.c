#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "redirect.h"
#include "pipe.h"

// Function to parse and execute the command
void parse_and_execute(char *command) {
    char *input_file = NULL;
    char *output_file = NULL;
    char *left_cmd[64];
    char *right_cmd[64];
    int i = 0;

    // Tokenize the command string
    char *token = strtok(command, " ");
    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " ");
            input_file = token;
        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " ");
            output_file = token;
        } else if (strcmp(token, "|") == 0) {
            // Split into left and right commands for the pipe
            left_cmd[i] = NULL;  // End the left command
            int j = 0;
            token = strtok(NULL, " ");
            while (token != NULL) {
                right_cmd[j++] = token;
                token = strtok(NULL, " ");
            }
            right_cmd[j] = NULL;  // End the right command
            execute_pipe(left_cmd, right_cmd);
            return;
        } else {
            left_cmd[i++] = token;
        }
        token = strtok(NULL, " ");
    }
    left_cmd[i] = NULL;  // End the left command

    // Handle redirection if specified
    if (input_file != NULL) {
        redirect_input(input_file);
    }
    if (output_file != NULL) {
        redirect_output(output_file);
    }

    // Execute the command
    if (fork() == 0) {
        execvp(left_cmd[0], left_cmd);
        perror("Command execution failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }
}

