# OS_Simulation
## How to Run
To compile, run ```make``` .<br />
Then, enter ```./run``` into your terminal.

### At the start, the program asks the user two questions:
How much RAM memory is there on the simulated computer? The program receives the number in bytes (no kilobytes or words). I can enter any number up to 4000000000 (4 billions).
How many hard disks does the simulated computer have? The enumeration of the hard disks starts from 0.


After that, the simulation begins. The program constantly listens for the user inputs and does NOT ask for a confirmation to enter another input. The user inputs signal some system events. The program simulates the corresponding system behaviour.

## Commands
```A  <priority> <size>``` <br />
‘A’ input means that a new common process has been created. When the new process arrives, your program should create its PCB and place the process in the ready-queue or the CPU. The requested amount of memory should be allocated for the new process. When choosing a PID for the new process start from 1 and go up. Do NOT reuse PIDs of the terminated processes. For example, the command A 5 1000 means that a new process with priority level 5 has been created and it requires 1000 bytes of memory.

```t``` <br />
currently running process terminates

```d  <disk_number> <cylinders>...``` <br />
The process that currently uses the CPU requests the hard disk #number. For example, the command d 0 2 5 18 means that the currently running process wants to read from the cylinders 2, 5, and 18 from the disk 0. Shortest-Seek-Time-First means that the OS always chooses to read the cylinder closes to the current head position. The starting position is 0. The requested cylinders for a process can be read in any order. The process returns to the ready-queue once all the cylinders are read. Pieces of different reading requests can be read in any order.

```D <disk_number>``` <br />
The hard disk #number has finished reading a cylinder.

```S r``` <br />
Shows what process is currently using the CPU and what processes are waiting in the ready-queue.

```S i``` <br />
Shows what processes are currently using the hard disks and what processes are waiting to use them. For each busy hard disk show the process that uses it and show its I/O-queue. The enumeration of hard disks starts from 0.

```S m``` <br />
Shows the state of memory. Show the range of memory addresses used by each process in the system.

## Instructions / Requirements
### Topics
**CPU scheduling:** Implement preemptive priority scheduling. The higher is the number the higher is the priotity.

**Disk I/O-queues are Shortest-Seek-Time-First.**

**Memory:** your program should simulate contiguous memory management with “First-fit” approach. You are not allowed to separately represent each byte of memory in your simulation.
