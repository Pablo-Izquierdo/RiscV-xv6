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
	
	ptr = shmem_access(3);
	if (ptr == NULL) {
		test_failed();
	}
	
	int pid = fork();
	if (pid < 0) {
		test_failed();
	}
	else if (pid == 0) {
		void *ptr2;

		ptr2 = shmem_access(3);
		if (ptr2 == NULL) {
			test_failed();
		}

		if (ptr != ptr2) {
			test_failed();
		}
		
		exit(0);	
	}
	else {
		wait(0);
	}

	test_passed();
	exit(0);
}
