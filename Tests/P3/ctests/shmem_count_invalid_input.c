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
	
	n = shmem_count(-1);
	if (n != -1) {
		test_failed();
	}

	n = shmem_count(-100);
	if (n != -1) {
		test_failed();
	}

	n = shmem_count(4);
	if (n != -1) {
		test_failed();
	}

	n = shmem_count(100);
	if (n != -1) {
		test_failed();
	}

	test_passed();
	exit(0);
}
