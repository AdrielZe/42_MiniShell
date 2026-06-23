# 42_MiniShell

## About the Project

The **Minishell** is a completed 42 project that implements a command interpreter inspired by Bash.

The goal of this project was to recreate the behavior of a real shell while following POSIX standards, handling processes, system calls, and inter-process communication. During development, the project provided a deeper understanding of operating systems concepts, command parsing, and process management.

This repository contains the final implementation developed collaboratively, following good programming practices and 42 coding standards.

---

## Implemented Features

- Interactive command prompt.
- Command execution with arguments.
- Input and output redirections:
    - `>`
    - `>>`
    - `<`
- Pipes:
    - `|`
- Environment variable handling.
- Variable expansion:
    - `$`
    - `~`
- Signal handling:
    - `Ctrl+C`
    - `Ctrl+D`
    - `Ctrl+\`
- Built-in commands:
    - `echo`
    - `cd`
    - `pwd`
    - `export`
    - `unset`
    - `env`
    - `exit`
- Error handling:
    - Invalid command handling.
    - Syntax error detection.
    - Correct exit status management.

---

## Technologies and Tools

- Language: **C**
- Operating System: **Linux**
- Libraries:
    - `readline` for command line input handling.
    - POSIX standard library functions.

---

## How to Compile

Make sure you have **gcc** and **Make** installed.

Clone the repository and run:

```bash
make
