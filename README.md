# 42_MiniShell

## About the Project
The **Minishell** is a 42 project that aims to create a small command interpreter based on Bash. The main challenge is to implement features of a real shell, ensuring compliance with practical behaviors and POSIX standards, while learning more about operating systems and inter-process communication.

This repository was created to document and organize the development of the project, which is being done collaboratively and following good programming practices.

---

## Required Features
- Implement a prompt that accepts and executes commands.
- Support the following Bash features:
    - Execution of commands with arguments.
    - Support for redirections (`>`, `>>`, `<`).
    - Pipes (`|`).
    - Environment variables.
    - Variable and special character expansion (`$`, `~`).
    - Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`).
- Implement builtins:
    - `echo`
    - `cd`
    - `pwd`
    - `export`
    - `unset`
    - `env`
    - `exit`
- Error management:
    - Friendly error messages for invalid commands or syntax errors.
    - Appropriate exit signaling (return status).

---

## Technologies and Tools
- Language: **C**
- Operating System: **Linux**
- Libraries:
    - `readline` for user input handling.
    - POSIX standard library functions.

---

## How to Compile
To compile the project, make sure you have the **gcc** compiler and **Make** installed. Use the following command:
```bash
make
