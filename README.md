# C++ Shell Project

A basic Unix-like shell implemented in C++ that supports a set of built-in commands and external command execution.

## Overview

This project implements a simple shell that reads user input from the terminal, parses commands, and executes them accordingly. It supports basic built-in commands such as `exit`, `echo`, `type`, `pwd`, and `cd`. For commands that are not built-in, the shell attempts to execute them as external programs using the system's PATH environment variable.

## Features

- **Command Parsing:** Supports tokenization of input including handling of both single and double quotes.
- **Built-in Commands:**
  - **exit:** Terminate the shell with an optional exit code.
  - **echo:** Print text to standard output with support for output redirection (both standard output and standard error).
  - **type:** Determine whether a command is a shell built-in or available in the PATH.
  - **pwd:** Display the current working directory.
  - **cd:** Change the current working directory.
- **External Command Execution:** If the command isn’t built into the shell, it uses the system’s environment to execute the command.
- **Output Buffering:** The shell flushes output buffers after every command ensuring immediate feedback on the terminal.

## Project Structure
```
.
├── main.cpp              # Entry point that handles input loop and command dispatch.
├── handle_commands.h     # Header file for command handling functions.
├── handle_commands.cpp   # Implementation of built-in command functions.
├── utils.h               # Header file for utility functions.
└── utils.cpp             # Implementation of utility functions (e.g., input parsing, PATH handling).
```

## Running the Shell

Launch the shell by running the executable:

```bash
./your_program.sh
```

You will see a prompt (`$ `) where you can type commands. Here are some examples:

- **Exit the shell:**
  ```bash
  $ exit 0
  ```
- **Echo a message and redirect stderr:**
  ```bash
  $ echo "exe with \'single quotes\'" 2> /tmp/bar/baz.md
  ```
- **Display the current directory:**
  ```bash
  $ pwd
  ```
- **Change directories:**
  ```bash
  $ cd /../../directory
  ```
- **Check the type of a command:**
  ```bash
  $ type cat
  ```

If a command is not recognized as a built-in, the shell will attempt to execute it as an external command. If the command is not found in the system PATH, a "command not found" message is displayed.

