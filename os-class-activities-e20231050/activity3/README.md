# Class Activity 3 — Socket Communication & Multithreading

**Student Name:** Vong Bunly  
**Student ID:** e20231050  
**Course:** Operating Systems  
**Date:** November 16, 2026

---

## Task 1: TCP Socket Server & Client (C)

### Implementation
Created a TCP server (`server.c`) and client (`client.c`) using C socket programming.

The server:
- Creates a TCP socket using `socket()`.
- Uses `setsockopt()` to allow address reuse.
- Binds to port 8081.
- Listens for incoming connections using `listen()`.
- Accepts a client connection using `accept()`.
- Receives a message and sends "Hello from server!".

The client:
- Creates a TCP socket.
- Connects to the server at `127.0.0.1:8081`.
- Sends "Hello from client!".
- Receives the server response.

Port 8081 was used because port 8080 was already occupied on the server.

### Results
The client successfully sent "Hello from client!" and received "Hello from server!". The server received the client message and returned its response.

### Questions and Answers

**1. What is the role of `bind()`? Why doesn't the client call it?**

`bind()` assigns a local IP address and port number to a socket. The server needs it to associate its socket with a known port so clients can connect. The client normally does not need to call `bind()` because the operating system automatically assigns an available local port when it connects.

**2. What does `accept()` return? How is it different from the listening socket?**

`accept()` returns a new socket descriptor for communicating with a specific connected client. The original listening socket remains available to accept other incoming connections. The new socket is used for data exchange with the accepted client.

**3. What happens if the client runs before the server?**

If the server is not listening, the client's connection attempt normally fails with a connection-refused error because no process is accepting connections at that address and port.

**4. What does `htons(PORT)` do?**

`htons()` means host-to-network short. It converts a 16-bit port number from the computer's host byte order to network byte order (big-endian), which is required for socket address structures.

**5. Draw the server/client socket call sequence.**

Server:
socket() → setsockopt() → bind() → listen() → accept() → read()/recv() → write()/send() → close()

Client:
socket() → connect() → write()/send() → read()/recv() → close()

---

## Task 2: POSIX Threads on Linux (C)

### Part A — Without Mutex
Created four POSIX threads using `pthread_create()`. Each thread increments the shared variable `shared_counter` 100,000 times.

The program did not consistently reach the expected value of 400,000. Several runs produced different lower values, demonstrating a race condition.

### Part B — With Mutex
Created a second program using `pthread_mutex_t`. Each thread locks the mutex before updating the shared counter and unlocks it afterward.

The final counter value was consistently 400,000.

### Questions and Answers

**1. What is a race condition? Why might `shared_counter` be incorrect?**

A race condition occurs when multiple threads access and modify shared data concurrently, and the result depends on their execution timing. Incrementing a counter involves reading, adding, and writing. These operations are not atomic, so threads can overwrite each other's updates, causing lost increments.

**2. What does `pthread_mutex_lock()` do? Why does it fix the problem?**

`pthread_mutex_lock()` locks a mutex so that only one thread at a time can enter the protected critical section. Other threads must wait until the mutex is unlocked. This prevents simultaneous updates to the shared counter and avoids lost increments.

**3. What happens if we forget `pthread_join()`?**

The main thread may finish and terminate the process before the worker threads complete their work. `pthread_join()` allows the main thread to wait for each worker thread to finish.

**4. What is the difference between a thread and a process?**

A process is an independent program in execution with its own address space and resources. Threads are execution units within a process. Threads in the same process share memory and resources such as code, data, heap, and open files, but each thread has its own stack and CPU register state.

---

## Task 3: Java Multithreading

### Part A — Extending Thread
Created `ThreadDemo.java` with three threads: Alpha, Beta, and Gamma. Each thread counts from 1 to 5 with a delay between counts. The main thread waits for all worker threads using `join()`.

### Part B — Implementing Runnable
Created `RunnableDemo.java` using the `Runnable` interface. Three tasks (Downloader, Processor, and Uploader) run concurrently in separate threads.

### Part C — Thread Pool
Created `PoolDemo.java` using `ExecutorService` with a fixed thread pool of two threads. Six tasks were submitted, and only two tasks ran concurrently.

### Questions and Answers

**1. What is the difference between extending `Thread` and implementing `Runnable`? When should we prefer `Runnable`?**

Extending `Thread` creates a class that is itself a thread. Implementing `Runnable` separates the task from the thread that executes it. `Runnable` is generally preferred when we want to separate task logic from thread management or when the class already extends another class.

**2. Why do only two tasks run simultaneously in `PoolDemo.java`?**

The program uses `Executors.newFixedThreadPool(2)`, which creates a pool with two worker threads. Therefore, at most two tasks can execute simultaneously. Remaining tasks wait in the queue until a worker becomes available.

**3. What does `thread.join()` do? What happens if it is removed?**

`join()` makes the calling thread wait until the specified thread finishes. Without it, the main thread may continue or finish before the worker threads complete, so the program may not wait for all tasks.

**4. What are the advantages of `ExecutorService`?**

`ExecutorService` manages thread creation and reuse, reduces the overhead of repeatedly creating threads, supports task submission and scheduling, and provides methods to shut down the pool and wait for task completion.

---

## Task 4: Observing Threads in Linux and Windows

### Part A — Linux Thread Observation

Created `threads_observe.c` with four worker threads. The main process and its worker threads were observed using `ps`, `/proc`, and `htop`.

**Observed results:**
- Process name: `threads_observe`
- Total number of threads: 5
- Main thread ID: 2412317
- Worker thread IDs: 2412320, 2412321, 2412322, and 2412323
- Process state: S (sleeping)

Commands used:

```bash
ps -eLf | grep '[t]hreads_observe'
ps -T -p 2412317
ls /proc/2412317/task/
ls /proc/2412317/task/ | wc -l
grep -E 'Name|State|Threads' /proc/2412317/status
