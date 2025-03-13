# Assignment 1: Basic UNIX Shell

This project implements a custom UNIX shell, developed as part of the Operating Systems course. It includes various functionalities like handling commands, managing background processes, handling input/output redirection, and built-in command handling. 

## Project Overview

This project was completed in multiple stages, each introducing new shell functionalities. The project is divided into six versions, each adding specific features to the shell. 

## Concepts and Features

### 1. Basic Command Handling
   - The shell accepts and executes basic commands using `fork()` and `exec()` system calls.
   - Commands are tokenized and parsed for easier handling in `parser.c`.

### 2. Background Process Management
   - Supports running processes in the background by appending `&` to commands.
   - Implemented using `waitpid()` with the `WNOHANG` option, allowing the shell to continue without waiting for background processes.

### 3. Input and Output Redirection
   - Redirects input (`<`) and output (`>`) for commands to/from files.
   - This feature was implemented using `dup2()` to replace standard input/output with specified files.

### 4. Command History
   - Tracks previously executed commands in the current session.
   - Commands are stored in an array and displayed upon entering `history`.

### 5. Built-in Commands
   - The shell includes built-in commands like `cd`, `exit`, and `history`:
     - **cd**: Changes the current directory.
     - **exit**: Exits the shell.
     - **history**: Displays the list of previously executed commands.

### 6. Variable Management
   - Supports defining and using environment variables within the shell.
   - Variables can be set with `export` and accessed using the `$` prefix.

---

## File Structure

- **main.c**: Contains the main loop and handles the execution of commands.
- **parser.c**: Manages command parsing, tokenization, and interpretation.
- **execute.c**: Handles execution of parsed commands, including background processes and redirection.
- **utils.c**: Provides utility functions for handling built-in commands and other common operations.

## Installation

Clone the repository to your local machine:

```bash
git clone https://github.com/naeemullah-datascientist/asgn_1_bsdsf22a029.git
cd asgn_1_bsdsf22a029/src
```

## Compilation

Compile the shell by running the following command:

```bash
gcc -o naeem_shell main.c parser.c execute.c utils.c
```

## Execution

Run the shell by executing:

```bash
./shell
(./a.out)
```

### Shell Usage

- **Basic Commands**: Run UNIX commands as you would in any other shell, e.g., `ls`, `pwd`, `echo`.
- **Background Processes**: Append `&` to run a process in the background, e.g., `sleep 10 &`.
- **Input/Output Redirection**: Use `>` to redirect output to a file and `<` to read input from a file, e.g., `cat < input.txt > output.txt`.
- **Command History**: Type `history` to see a list of executed commands.
- **Change Directory**: Use `cd <directory>` to navigate directories.
- **Exit Shell**: Type `exit` to terminate the shell.

---

## Known Bugs and Limitations

- **Redirection in Built-in Commands**: Some built-in commands might not support redirection.
- **Background Process Handling**: Limited support for managing multiple background processes.

---

## Acknowledgments

Special thanks to the Operating Systems course instructor and teaching assistants for guidance and resources that supported the development of this project.

--- 
## Contributors and Acknowledgments

Special thanks to my TA and mentor:

- [Abdul Qadir](https://github.com/AbdulQadir4) – Teaching Assistant for Operating Systems course
- [Arif Butt](https://github.com/arifbutt) – Guidance and support throughout the project
---
