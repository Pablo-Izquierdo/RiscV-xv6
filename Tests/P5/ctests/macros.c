#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

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

  if (T_SMALLFILE != 4) {
	  test_failed();	
  }

  if (O_SMALLFILE != 0x800) {
	  test_failed();	
  }

  test_passed();
  exit(0);
}
