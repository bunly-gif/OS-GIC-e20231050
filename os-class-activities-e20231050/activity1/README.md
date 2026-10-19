# Activity 1: System Calls in Practice

**Student ID:** e20231050

## Overview

This activity explores how user programs interact with the operating system through system calls and library functions. It also examines directory operations, system call tracing with `strace`, and basic Linux system information.

## Task 1: System Calls and Library Functions

This task compares programs that use library functions with programs that invoke system calls directly.

### Programs
- `file_creator_lib.c`
- `file_creator_sys.c`
- `file_reader_lib.c`
- `file_reader_sys.c`

### Screenshots
See the `screenshots/` directory for the creator and reader program outputs.

## Task 2: Directory Listing

This task compares directory listing programs implemented using library functions and direct system calls.

### Programs
- `dir_list_lib.c`
- `dir_list_sys.c`

### Observations
The two programs perform directory listing using different approaches. The library version uses library functions, while the system-call version interacts with the operating system through system calls.

### Screenshots
- `task2_lib.png`
- `task2_sys.png`

## Task 3: System Call Tracing with strace

This task uses `strace` to observe and compare the system calls made by programs that use library functions and direct system calls.

### Trace files
- `strace_lib_task1.txt`
- `strace_sys_task1.txt`
- `strace_lib_reader.txt`
- `strace_sys_reader.txt`
- `strace_summary_lib.txt`
- `strace_summary_sys.txt`

### Observations
- Both creator programs open or create the output file, write data, and close the file.
- Both reader programs read the file contents and write the contents to standard output.
- The library and direct system-call implementations may differ in the number and type of system calls used.
- The `strace` summaries help identify system-call activity and errors.

### Screenshots
The `screenshots/` directory contains annotated traces and summary comparisons.
## Task 4: Linux System Information

This task explores Linux system information, process information, loaded kernel modules, and the relationship between user space, the kernel, and hardware.

### Information collected
- System and kernel information using `uname`.
- CPU and memory information from `/proc`.
- Process information from `/proc/self/status`.
- Loaded kernel modules using `lsmod`.

### Screenshots
- `task4_system_info.png`
- `task4_process_info.png`
- `task4_modules.png`
- `task4_os_layers_diagram.png`

## Reflection

This activity helped me understand how programs interact with the operating system through library functions and system calls. Using `strace` made it possible to observe system-call activity, while exploring `/proc` and kernel modules provided insight into Linux system information and process management.

## Submission Notes

The source files, command records, trace outputs, and screenshots are organized in their respective folders.

The `hello_winapi.png` screenshot is not included because this activity was completed in an Ubuntu environment.
