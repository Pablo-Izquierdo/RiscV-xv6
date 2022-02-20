/* clone and play with the argument */
#include "kernel/types.h"
#include "user/user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

int ppid;
volatile int arg = 55;
volatile int global = 1;

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

   int clone_pid = clone(worker, (void*)&arg, stack);
   assert(clone_pid > 0);
   while(global != 55);
   assert(arg == 1);
   printf("TEST PASSED\n");
   exit(0);
}

void
worker(void *arg_ptr) {
   int tmp = *(int*)arg_ptr;
   *(int*)arg_ptr = 1;
   assert(global == 1);
   global = tmp;
   exit(0);
}
