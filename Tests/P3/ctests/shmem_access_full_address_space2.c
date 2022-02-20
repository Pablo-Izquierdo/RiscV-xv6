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
  ptr = shmem_access(0);
  if (ptr == NULL) {
    test_failed();
  }
  
  void *ptr2;
	while (1) {
		ptr2 = sbrk(1024);
    if (ptr2 >= ptr && ptr2 != (char *) -1) {
      test_failed();
    }
    
		if (ptr2 == (char *) -1) {
			break;
		}
	}
  
	test_passed();
	exit(0);
}
