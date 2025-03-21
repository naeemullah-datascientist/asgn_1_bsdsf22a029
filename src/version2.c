#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>

#define BUFFER_SIZE 1024

void display_prompt() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("PUCITshell@%s:- ", cwd);
    } else {
        perror("getcwd() error");
    }
}

char* read_input() {
    char *buffer = NULL;
    size_t bufsize = 0;
    getline(&buffer, &bufsize, stdin);
    return buffer;
}

char** parse_input(char* input) {
    int bufsize = BUFFER_SIZE, position = 0;
    char** tokens = malloc(bufsize * sizeof(char*));
    char* token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, " \t\r\n\a");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += BUFFER_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Reallocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

int execute_command(char** args) {
    int in_redirect = -1, out_redirect = -1;
    int i = 0;

    while (args[i] != NULL) {
        if (strcmp(args[i], "<") == 0) {
            in_redirect = open(args[i + 1], O_RDONLY);
            if (in_redirect < 0) {
                perror("Error opening input file");
                return 1;
            }
            args[i] = NULL;  // Remove redirection from args
        } else if (strcmp(args[i], ">") == 0) {
            out_redirect = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (out_redirect < 0) {
                perror("Error opening output file");
                return 1;
            }
            args[i] = NULL;  // Remove redirection from args
        }
        i++;
    }

    pid_t pid = fork();
    if (pid == 0) {  // Child process
        // Handle input redirection
        if (in_redirect != -1) {
            dup2(in_redirect, STDIN_FILENO);
            close(in_redirect);
        }
        // Handle output redirection
        if (out_redirect != -1) {
            dup2(out_redirect, STDOUT_FILENO);
            close(out_redirect);
        }

        if (execvp(args[0], args) == -1) {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);

    } else if (pid < 0) {  // Fork error
        perror("Error forking");

    } else {  // Parent process
        waitpid(pid, NULL, 0);  // Wait for child process to complete
    }

    return 1;
}

int main() {
    char* input;
    char** args;
    int status = 1;

    do {
        display_prompt();
        input = read_input();

        if (feof(stdin)) {
            printf("\n");
            break;
        }

        args = parse_input(input);
        if (args[0] != NULL) {
            status = execute_command(args);
        }

        free(input);
        free(args);
    } while (status);

    return 0;
}

