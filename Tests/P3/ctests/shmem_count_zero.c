#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "stddef.h"

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
 	int n;
  int i;
  
  for (i = 0; i < 4; i++) {
    n = shmem_count(i);
    if (n != 0) {
      test_failed();
    }
  }

	test_passed();
	exit(0);
}
