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
  
  for (i = 3; i >= 0; i--) {
    ptr = shmem_access(i);
    if (ptr == NULL) {
      test_failed();
    }
    
    *ptr = 'c';
  }
	
	test_passed();
	exit(0);
}
