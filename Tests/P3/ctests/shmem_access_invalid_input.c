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
  void *ptr;
	
	ptr = shmem_access(-1);
	if (ptr != NULL) {
		test_failed();
	}

	ptr = shmem_access(-100);
	if (ptr != NULL) {
		test_failed();
	}

	ptr = shmem_access(4);
	if (ptr != NULL) {
		test_failed();
	}

	ptr = shmem_access(100);
	if (ptr != NULL) {
		test_failed();
	}

	test_passed();
	exit(0);
}
