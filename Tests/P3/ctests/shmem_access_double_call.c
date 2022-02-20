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
	void *ptr2;
	
	ptr = shmem_access(3);
	if (ptr == NULL) {
		test_failed();
	}

	ptr2 = shmem_access(3);
	if (ptr == NULL) {
		test_failed();
	}

	if (ptr != ptr2) {
		test_failed();
	}

	test_passed();
	exit(0);
}
