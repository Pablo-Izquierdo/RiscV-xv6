#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"


#define assert(x) if (x) { /* pass */ } else { \
   printf("assert failed %s %s %d\n", #x , __FILE__, __LINE__); \
   exit(-1); \
   }


// Test5: processes first increase, then decrease.
int
main(int argc, char *argv[])
{
  int i, num_child = 5;
  for (i = 0; i < num_child; i++) {
    if (fork() == 0) {
      exit(0);
    }
  }
  
  // printf(1, "%d processes are currently running.\n", getprocs());
  assert(getprocs() == (3 + num_child));

  int num_left = 3;
  for (i = num_child; i > num_left; i--) {
    wait(0);
  }
  // printf(1, "%d processes are currently running.\n", getprocs());
  assert(getprocs() == (3 + num_left));

  printf("TEST PASSED\n");

  for (i = num_left; i >= 0; i--) {
    wait(0);
  }
  exit(0);
}
