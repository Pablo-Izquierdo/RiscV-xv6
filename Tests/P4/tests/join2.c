/* join argument checking */
#include "kernel/types.h"
#include "user/user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

int ppid;
int global = 1;

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

   int arg = 42;
   int clone_pid = clone(worker, &arg, stack);
   assert(clone_pid > 0);

   sbrk(PGSIZE);
   void **join_stack = (void**) ((uint64)sbrk(0) - 8);
   assert(join((void**)((uint64)join_stack + 2)) == -1);
   assert(join(join_stack) == clone_pid);
   assert(stack == *join_stack);
   assert(global == 2);

   printf("TEST PASSED\n");
   exit(0);
}

void
worker(void *arg_ptr) {
   int arg = *(int*)arg_ptr;
   assert(arg == 42);
   assert(global == 1);
   global++;
   exit(0);
}
