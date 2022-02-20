/* clone copies file descriptors, but doesn't share */
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/riscv.h"

#undef NULL
#define NULL ((void*)0)

//#define PGSIZE (4096)

int ppid;
volatile uint newfd = 0;

#define assert(x) if (x) {} else { \
   printf("%s: %d ", __FILE__, __LINE__); \
   printf("assert failed (%s)\n", # x); \
   printf("TEST FAILED\n"); \
   kill(ppid); \
   exit(0); \
}
void worker(void *arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();
   void *stack = malloc(PGSIZE*2);
   assert(stack != NULL);
   if((uint64)stack % PGSIZE)
     stack = stack + (4096 - (uint64)stack % PGSIZE);

   int fd = open("tmp", O_WRONLY|O_CREATE);
   assert(fd == 3);
   int clone_pid = clone(worker, 0, stack);
   assert(clone_pid > 0);
   while(!newfd);
   assert(write(newfd, "goodbye\n", 8) == -1);
   printf("TEST PASSED\n");
   exit(0);
}

void
worker(void *arg_ptr) {
   assert(write(3, "hello\n", 6) == 6);
   __sync_lock_test_and_set(&newfd, open("tmp2", O_WRONLY|O_CREATE));
   exit(0);
}
