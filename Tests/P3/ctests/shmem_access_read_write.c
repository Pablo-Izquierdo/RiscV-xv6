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
  char *ptr;
	int i;

	for (i = 0; i < 4; i++) {
		ptr = shmem_access(i);
		if (ptr == NULL) {
			test_failed();
		}

		char c = 'c';
		ptr[100] = c; //write
	
		char d = *(ptr+100); //read

		if (c != d) {
			test_failed();
		}
	}
	
	test_passed();
	exit(0);
}
