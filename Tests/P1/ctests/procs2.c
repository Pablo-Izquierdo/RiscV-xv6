#include "kernel/types.h"
#include "user/user.h"

#define assert(x) if (x) { /* pass */ } else { \
   printf("assert failed %s %s %d\n", #x , __FILE__, __LINE__); \
   exit(-1); \
   }


// Test2: 2 + 1 sleeping and 1 running
int
main(int argc, char *argv[])
{
  if (fork() == 0) {
    // printf(1, "%d processes are currently running.\n", getprocs());
    assert(getprocs() == 4);
    printf("TEST PASSED\n");
  } else {
    wait(0);
  }

  exit(0);
}
