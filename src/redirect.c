#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to handle input redirection
void redirect_input(const char *file) {
    int fd = open(file, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
}

// Function to handle output redirection
void redirect_output(const char *file) {
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

