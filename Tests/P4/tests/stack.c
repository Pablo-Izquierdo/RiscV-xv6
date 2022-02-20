/* set up stack correctly (and without extra items) */
#include "kernel/types.h"
#include "user/user.h"

#undef NULL
#define NULL ((void*)0)

int ppid;
#define PGSIZE (4096)

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

   int clone_pid = clone(worker, stack, stack);
   assert(clone_pid > 0);
   while(global != 5);
   printf("TEST PASSED\n");
   exit(0);
}

void
worker(void *arg_ptr) {
   printf("dir = %d, contenido = %d\n", &arg_ptr, arg_ptr + PGSIZE - 8);
   assert((uint64)&arg_ptr == ((uint64)arg_ptr + PGSIZE - 40));
   assert(*((uint64*) (arg_ptr + PGSIZE - 16)) == 0xffffffff);
   global = 5;
   exit(0);
}
