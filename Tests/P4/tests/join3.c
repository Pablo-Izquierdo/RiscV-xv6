/* join should not handle child processes (forked) */
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

int
main(int argc, char *argv[])
{
   ppid = getpid();

   int fork_pid = fork();
   if(fork_pid == 0) {
     exit(0);
   }
   assert(fork_pid > 0);

   void *join_stack;
   int join_pid = join(&join_stack);
   assert(join_pid == -1);

   printf("TEST PASSED\n");
   exit(0);
}
