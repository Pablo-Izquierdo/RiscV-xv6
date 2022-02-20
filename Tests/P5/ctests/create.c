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
  struct stat st;
  
  if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE)) < 0){
    printf("Failed to create a small file\n");
    test_failed();
    exit(0);
  }
  
  if(fstat(fd, &st) < 0){
    close(fd);
    printf("Failed to get stat on the small file\n");
    test_failed();
    exit(0);
  }
  
  if (st.type != T_SMALLFILE) {
    printf("Did not create a small file\n");
    test_failed();
  }
  else {
    test_passed();
  }
  
	exit(0);
}
