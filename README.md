Pipex – 42 School Project
## Overview

pipex is a systems programming project from the 42 curriculum focused on process creation and inter-process communication.

The objective is to recreate the behavior of a simple shell pipeline:

< infile cmd1 | cmd2 > outfile

The program must execute two commands in sequence, redirect input and output correctly, and connect them using UNIX pipes.

## Project Scope

The project includes:

Parsing command-line arguments

Creating child processes using fork()

Executing commands with execve()

Creating and managing pipes with pipe()

Redirecting input and output using dup2()

Resolving executable paths from the PATH environment variable

Handling errors and exit codes properly

Ensuring clean memory and file descriptor management

Implemented in:

C

UNIX system calls

Project Focus

pipex focuses on:

Understanding how shell pipelines work internally

Managing file descriptors across multiple processes

Controlling process lifecycle and synchronization

Handling environment variables and command resolution

Structuring logic around low-level system calls

## Technical Scope

The project explores fundamental UNIX mechanisms behind command execution. It involves duplicating file descriptors, connecting process outputs to inputs through pipes, and ensuring proper execution flow across parent and child processes.

Particular attention is given to:

Correct ordering of fork, pipe, and dup2 calls

Preventing file descriptor leaks

Handling execution failures safely

Managing multiple processes deterministically

The emphasis is on understanding how shells coordinate processes and how data flows between them at the system level.

## Build & Run
make
./pipex infile "cmd1" "cmd2" outfile
