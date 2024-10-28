#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void parse_and_execute(char *command) {
    char *input_file = NULL;
    char *output_file = NULL;
    char *left_cmd[64];
    char *right_cmd[64];
    int i = 0;

    // Tokenize the command string
    char *token = strtok(command, " ");
    if (token == NULL) return; // Early return if no command is given

    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " ");
            if (token != NULL) input_file = token; // Get input file name
        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " ");
            if (token != NULL) output_file = token; // Get output file name
        } else if (strcmp(token, "|") == 0) {
            // End left command
            left_cmd[i] = NULL; // Null-terminate the left command
            int j = 0;
            token = strtok(NULL, " ");
            // Collect right command
            while (token != NULL) {
                right_cmd[j++] = token;
                token = strtok(NULL, " ");
            }
            right_cmd[j] = NULL; // Null-terminate the right command

            // Execute pipe
            execute_pipe(left_cmd, right_cmd);
            return; // Exit after executing pipe
        } else {
            left_cmd[i++] = token; // Collect left command
        }
        token = strtok(NULL, " ");
    }
    left_cmd[i] = NULL; // Null-terminate left command

    // Handle input/output redirection
    if (input_file != NULL) {
        redirect_input(input_file);
    }
    if (output_file != NULL) {
        redirect_output(output_file);
    }

    // Execute the command
    if (fork() == 0) {
        execvp(left_cmd[0], left_cmd); // Execute command
        perror("Command execution failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL); // Wait for command to finish
    }
}
