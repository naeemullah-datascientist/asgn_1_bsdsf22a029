# Assignment 1: Basic UNIX Shell

This repository contains the source code for Assignment 1 of the Operating Systems course. The goal of this assignment is to implement a basic UNIX shell that can execute commands entered by the user.

## Project Overview
The shell program, named `basic_shell`, displays a prompt, reads user input, parses the input command, creates a child process to execute the command, and waits for the process to complete before displaying the prompt again.

## Getting Started

### Prerequisites
- A Linux environment (Kali Linux recommended)
- GCC compiler installed (to compile the C program)

### How to Compile the Shell
To compile the shell program, navigate to the project directory and run:
```bash
gcc basic_shell.c -o basic_shell
How to Run the Shell
To run the shell, execute the following command:
./basic_shell
The shell prompt will appear as NAEEMshell:-, indicating it is ready to accept commands.

Features Implemented
Basic shell prompt displaying the current directory
Command parsing and execution using fork(), execvp(), and waitpid()
Handling of basic commands such as ls, pwd, cd, and exit
Graceful handling of the CTRL+D command to exit the shell
Known Issues/Bugs
The cd command might not work as expected in some cases.
Error handling is basic and could be improved.
To-Do List
Add support for environment variables
Implement additional built-in commands like history, echo, etc.
Improve error handling and user feedback
Acknowledgments
Course Instructor: Arif@pucit.edu.pk
Teaching Assistant: 0xabdulqadir@gmail.com
Online resources consulted for this project include various C programming tutorials and UNIX shell programming guides.
