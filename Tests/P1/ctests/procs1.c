#include "kernel/types.h"
#include "user/user.h"

#define assert(x) if (x) { /* pass */ } else { \
   printf("assert failed %s %s %d\n", #x , __FILE__, __LINE__); \
   exit(-1); \
   }


// Test1: 2 sleeping, 1 running
int
main(int argc, char *argv[])
{
  // printf(1, "%d processes are currently running.\n", getprocs());
  assert(getprocs() == 3);
  printf("TEST PASSED\n");
  exit(0);
}
