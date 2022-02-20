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
  int fd;
  
  char *filename = "test_file.txt";
  if((fd = open(filename, O_SMALLFILE | O_RDWR)) >= 0){
    printf("Created small file even though O_CREATE was never passed in.\n");
    test_failed();
  }
  
  test_passed();
  exit(0);
}
