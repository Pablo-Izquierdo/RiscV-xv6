/* clone with bad stack argument */
#include "kernel/types.h"
#include "user/user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

int ppid;

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
   if((uint64)stack % PGSIZE == 0)
     stack += 4;

   assert(clone(worker, 0, stack) == -1);

   stack = sbrk(0);
   if((uint64)stack % PGSIZE)
      stack = stack + (PGSIZE - (uint64)stack % PGSIZE);
   sbrk( ((uint64)stack - (uint64)sbrk(0)) + PGSIZE/2 );
   assert((uint64)stack % PGSIZE == 0);
   assert((uint64)sbrk(0) - (uint64)stack == PGSIZE/2);

   assert(clone(worker, 0, stack) == -1);

   printf("TEST PASSED\n");
   exit(0);
}

void
worker(void *arg_ptr) {
   exit(0);
}
