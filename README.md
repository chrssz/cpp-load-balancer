# cpp-load-balancer

A multithreaded HTTP load balancer built from scratch in C++20, 
using raw Winsock2 sockets and no networking libraries.

## Current Progress
###Server (`src/server`)
Responsible for handling the WSA setup, initializations of needed classes, Listening for socket connections, and handing off tasks to thread pool

### Socket Layer (`src/socket`)
A Winsock2 socket abstraction built around three classes:

- **`SocketWrapper`** — base class owning a raw `SOCKET` handle, 
  handles creation and cleanup via RAII
- **`ListeningSocket`** — binds to a port, listens for incoming 
  connections, and accepts clients in a loop
- **`ConnectedSocket`** — represents one accepted client connection, 
  used for reading requests and sending responses

### Thread Pool (`src/thread pool`)

A task based thread pool for handling accepted connections 
concurrently. Accepted `ConnectedSocket`s are handed off as 
tasks to worker threads. Worker threads are initialize using jthreads.

### Thread Safe Queue (`src/utils/conccurency.h`)
A thread safe queue that handles safe read/write access. Threads hold mutexes with locking capabilities from unique_lock for manual unlock/lock capabilities. Threads are also put on 'wait' using conditon variables cv.wait(), Once a task is queued up a thread is awoken using cv.notifyone(). std::stop_token utilized to flag any running threads to stop to allow for a clean shutdown.

## Architecture Goal
