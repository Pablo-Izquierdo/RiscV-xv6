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
  
	while (1) {
		ptr = sbrk(1024);
		if (ptr == (char *) -1) {
			break;
		}
	}
	
	ptr = shmem_access(0);
	if (ptr != NULL) {
		test_failed();
	}

	test_passed();
	exit(0);
}
