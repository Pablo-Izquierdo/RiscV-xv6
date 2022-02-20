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
	char arr[6] = "CS537";
	
	ptr = shmem_access(2);
	if (ptr == NULL) {
		test_failed();
	}

	int pid = fork();
	if (pid < 0) {
		test_failed();
	}
	else if (pid == 0) {
		sleep(20);
		
		for (i = 0; i < 5; i++) {
			if (*(ptr+i) != arr[i]) {
				test_failed();
			}
		}
	}
	else {
		for (i = 0; i < 5; i++) {
			*(ptr+i) = arr[i];
		}
		
		wait(0);
	}

	test_passed();
	exit(0);
}
