#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"

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

#define NITERATIONS 1000

int
main(int argc, char *argv[])
{
  int fd;
  char buf[NITERATIONS];
  char result; //character read from file
  int n;
  int i;
  
  for(i = 0; i < NITERATIONS; i++){
    buf[i] = (char)(i+(int)'0');
  }
  
  //open, write 1 byte, close
  for(i = 0; i < NITERATIONS; i++){
    if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE | O_RDWR)) < 0){
      printf("Failed to create the small file\n");
      test_failed();
    }
    if((n = write(fd, &buf[i], 1)) != 1){
      printf("Write failed!\n");
      test_failed();
    }
    close(fd);
  }
  
  //read
  if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE | O_RDWR)) < 0){
    printf("Failed to open the small file\n");
    test_failed();
  }
  if((n = read(fd, &result, 10)) != 1){
    printf("Read failed! %d\n", n);
    test_failed();
  }
  close(fd);
  
  if(result != buf[NITERATIONS-1]){
    printf("Data mismatch.\n");
    test_failed();
  }

  test_passed();
	exit(0);
}
