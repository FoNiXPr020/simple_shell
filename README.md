# Simple Shell Project

## Overview
This project, developed by Spencer Cheng with contributions from Julien Barbier, is a team-based effort to create a simple Unix shell. The team members for this project are Godswill Kalu and Vatalis Ibeh.

## Learning Objectives
Upon completion of this project, you should be able to:

- Explain the design and implementation of the original Unix operating system.
- Identify the author of the first version of the UNIX shell.
- Recognize the creator of the B programming language (the direct predecessor to the C programming language).
- Understand the role of Ken Thompson in the development of Unix.
- Comprehend the workings of a shell.
- Define PID (Process ID) and PPID (Parent Process ID).
- Manipulate the environment of the current process.
- Differentiate between a function and a system call.
- Create processes in a Unix environment.
- Understand the three prototypes of the main function.
- Explain how the shell uses the PATH to locate programs.
- Execute another program using the `execve` system call.
- Suspend the execution of a process until one of its children terminates.
- Define EOF (End-of-File).

## Requirements

### General
- Allowed editors: vi, vim, emacs.
- All files will be compiled on Ubuntu 20.04 LTS using gcc, with the options: `-Wall -Werror -Wextra -pedantic -std=gnu89`.
- All files should end with a new line.
- Follow the Betty style for code. It will be checked using `betty-style.pl` and `betty-doc.pl`.
- Ensure there are no memory leaks in your shell.
- Limit each file to no more than 5 functions.
- Use include guards for all header files.
- Use system calls only when necessary.

### GitHub
- Maintain one project repository per group.
- If both partners have repositories with the same name, a 0% score may be assigned.
- Add your partner as a collaborator.

### Output
- Ensure your program produces the same output as `/bin/sh` and the same error output.
- When printing an error, the program name must be equivalent to `argv[0]`.

### List of Allowed Functions and System Calls
`access`, `chdir`, `close`, `closedir`, `execve`, `exit`, `_exit`, `fflush`, `fork`, `free`, `getcwd`, `getline`, `getpid`, `isatty`, `kill`, `malloc`, `open`, `opendir`, `perror`, `read`, `readdir`, `signal`, `stat` (`__xstat`), `lstat` (`__lxstat`), `fstat` (`__fxstat`), `strtok`, `wait`, `waitpid`, `wait3`, `wait4`, `write`.

## Compilation
Your shell will be compiled using the following command:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Authors

- [Mohamed Barhoun](https://github.com/FoNiXPr020)
