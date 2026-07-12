# cpp-load-balancer

A multithreaded HTTP load balancer built from scratch in C++20, 
using raw Winsock2 sockets and no networking libraries.

## Current Progress

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
tasks to worker threads, so the listening loop is never blocked 
waiting for a client to finish.

## Architecture Goal
