#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "stddef.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"
#include "kernel/riscv.h"

void
test_failed()
{
  printf("TEST FAILED\n");
  exit(0);
}

void
test_passed()
{
  printf("TEST PASSED\n");
  exit(0);
}

int
main(int argc, char *argv[])
{
  char *ptr;
  int i;
  
  ptr = shmem_access(3);
  if (ptr == NULL) {
    test_failed();
  }
  
  char arr[4] = "tmp";
  for (i = 0; i < 4; i++) {
    *(ptr+i) = arr[i];
  }
  
  //argstr
  int fd = open(ptr, O_WRONLY|O_CREATE);
  if (fd == -1) {
    printf("open system call failed to take a string from within a shared page\n");
    test_failed();
  }
  
  //argptr
  int n = write(fd, ptr, 10);
  if (n == -1) {
    printf("write system call failed to take a pointer from within a shared page\n");
    test_failed();
  }
  
  //making sure invalid strings are still caught
  int fd2 = open((char *)(MAXVA/2), O_WRONLY|O_CREATE);
  if (fd2 != -1) {
    printf("open system call successfully accepted an invalid string\n");
    test_failed();
  }
  
  //making sure invalid pointers are still caught
  n = write(fd, (char *)(MAXVA/2), 10);
  if (n != -1) {
    printf("write system call successfully accepted an invalid pointer\n");
    test_failed();
  }
  
  //making sure edge case is checked
  n = write(fd, (char *)(ptr + 4094), 10);
  if (n != -1) {
    printf("write system call successfully accepted an overflowing pointer in a shared page\n");
    test_failed();
  }
  
  test_passed();
  exit(0);
}
