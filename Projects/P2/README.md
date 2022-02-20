# Project 2: xv6 Scheduler
[TOC]
## Objectives

There are two objectives to this assignment:

*   To familiarize yourself with a real scheduler.
*   To change that scheduler to a new algorithm.

## Updates

Read these updates to keep up with any small fixes in the specification.

 >NONE

## Overview

In this project, you'll be putting a new scheduler into xv6\. It is called a simple **priority-based scheduler** . The basic idea is simple: assign each running process a **priority,** which is an integer number, in this case either 1 (low priority) or 2 (high priority). At any given instance, the scheduler should run processes that have the high priority (2). If there are two or more processes that have the same high priority, the scheduler should round-robin between them. A low-priority (level 1) process does NOT run as long as there are high-priority jobs available to run. Note that this is a simpler scheduler than the one discussed in the book chapter on [MLFQ.](http://www.ostep.org/cpu-sched-mlfq.pdf)

## Details

You will need to implement a couple of new system calls to implement this scheduler. The first is **int setpri(int num),** which sets the priority for the calling process. By default, each process should get a priority of 1; calling this routine makes it such that a process can raise or lower its priority. The argument of the system call is either **1** or **2**.

The second is __int getpinfo(struct pstat *).__ This routine returns some basic information about each running process (through the pointer), including how long it has run at each priority (measured in clock ticks) and its process ID. You can use this system call to build a variant of the command line program **ps,** which can then be called to see what is going on.

If either of these calls are passed bad parameters, **return -1** to indicate a failure. Otherwise, **return 0** upon success.

One thing you'll have to do is make sure to initialize the priority of a process correctly. All processes, when created, should start at priority level 1\. Only by calling **setpri()** can a process change its priority to 2.

When a bad priority (not 1 or 2) is passed to your setpri() system call, **return -1** (indicating an error). Otherwise return 0 (indicating success). Similarly, if a bad pointer is passed to your **getpinfo()** call, **return -1**; otherwise, if the call is successful, **return 0**.

In your Makefile, replace `CPUS := 2` with `CPUS := 1` . The old setting runs xv6 with two CPU cores, but you only need to do scheduling for a single core in this project.

## Tips
In order to maintain the complexity of the lab attained, we assume that the priority will be not inherited after performing a `fork()`.

Most of the code for the scheduler is quite localized and can be found in **proc.c.** The associated header file, **proc.h** is also quite useful to examine. To change the scheduler, not much needs to be done; study its control flow and then try some small changes.

You'll need to understand how to fill in the structure **pstat** in the kernel and pass the results to user space. The structure looks like:

```c
#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

struct pstat {
    int inuse[NPROC];  // whether this slot of the process process table is in use (1 or 0)
    int pid[NPROC];    // the PID of each process
    int hticks[NPROC]; // the number of ticks each process has accumulated at priority 2
    int lticks[NPROC]; // the number of ticks each process has accumulated at priority 1
};


#endif // _PSTAT_H_
```
**getpinfo(struct pstat *)** syscall interface is a bit complex. We should allocate a *pstat* struct variable in the user space and instruct to the system call that the results 
of it should be stored there. In other words, we pass a pointer to where we want the output results. In order to perform complex parameters in system calls (like this one)
we need to access from the system call routine to the user stack pointer. Xv6 provides some helpers to do that. Take look at the [xv6 book.](https://pdos.csail.mit.edu/6.828/2014/xv6/book-rev8.pdf) and search for **argint/argptr** description.

**Random xv6 tip I:** To run the xv6 environment, use **make qemu-nox.** Doing so avoids the use of X windows and is generally fast and easy. However, quitting is not so easy; to quit, you have to know the shortcuts provided by the machine emulator, qemu. Type **control-a** followed by **x** to exit the emulation. There are a few other commands like this available; to see them, type **control-a** followed by an **h.**

**Random xv6 tip II:** To debug the xv6 kernel you need two terminals. For example you can open a **tmux** session with two pannes with **ctr-B and %**, or and aditional ssh session in the working directory with **vagrant ssh**. Next we show how to debug a system call such as **fork()**.

```code
host[1]$ make qemu-nox-gdb
host[2]$ gdb -tui kernel
(gdb) target remote localhost:26000
(gdb) continue
(gdb) ^C
(gdb) break fork
host[1]$ ls
host[2]$
(gdb) step #to jump into allocproc
(gdb) next
(gdb) print p->name #should print init (process 0)
(gdb) br 41 #to place a breakpoint into first available entry
(gdb) continue 
(gdb) ... etc ... etc...  
```

## The Code

This kernel was developed by [MIT OS Enegeneering](https://pdos.csail.mit.edu/6.828/2016/). Nevertheless, the version used here has been ´reorganized by OSTEP author. We will use that version (which is avaliable in **../xv6/xv6-wisc/**).

You may also find the following readings about xv6 useful, written by the same team that ported xv6 to x86: [xv6 book.](https://pdos.csail.mit.edu/6.828/2014/xv6/book-rev8.pdf) However, remeber that the kernel version we use is a little different than the book.

# <span style="color:red;">Rules of delivery </span>

Follow this rules in order to be graded. If some of them ignored, the Lab will be not graaded.

* All the changes should be restricted to projects working dir (i.n. Project X/). Changes out of that path (i.s. wrongfully done meges/rebases/whatever_git_related_thing) will invalidate the Lab
* The directory of xv6 should be called ´xv6´ (the changes should be in ´Projects/P2/xv6/´)
* The Lab will be fetched at deadline. Any subsequent change will be ignored for the grading.

## Reference

Use at least version 1.23 of [vpuente/AOSUC1516](https://app.vagrantup.com/vpuente/boxes/AOSUC) vagrant box. This box includes all the tools required to perform the project (gcc, qemu, shared dirs with the guest, etc...). Create a instance in this directory and copy xv6 code to start working in your branch.



<!-- To many things are incorrect [![Intro (spanish)](http://img.youtube.com/vi/gHoTn525BP8/0.jpg)](https://www.youtube.com/watch?v=gHoTn525BP8) -->



**Particularly useful for this project: Chapters 7-9**



