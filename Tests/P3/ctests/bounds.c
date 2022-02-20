#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#undef NULL
#define NULL ((void*)0)

#define assert(x) if (x) {} else { \
   printf("%s: %d ", __FILE__, __LINE__); \
   printf("assert failed (%s)\n", # x); \
   printf("TEST FAILED\n"); \
   exit(0); \
}

int
main(int argc, char *argv[])
{
  char *arg;

  int fd = open("tmp", O_WRONLY|O_CREATE);
  assert(fd != -1);

  /* at zero */
  arg = (char*) 0x0;
  assert(write(fd, arg, 10) == -1);

  /* within null page */
  arg = (char*) 0x400;
  assert(write(fd, arg, 1024) == -1);

  /* spanning null page and code */
  arg = (char*) 0xfff;
  assert(write(fd, arg, 2) == -1);

  printf("TEST PASSED\n");
  exit(0);
}
