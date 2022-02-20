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

#define MAX 52

int
main(int argc, char *argv[])
{
  int fd;
  char buf[MAX];
  char buf2[MAX];
  int n;
  int i;
  
  for(i = 0; i < MAX; i++){
    buf[i] = (char)(i+(int)'0');
  }
  memset(buf2, 0, MAX);
  
  //create and write
  if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE | O_RDWR)) < 0){
    printf("Failed to create the small file\n");
    test_failed();
    exit(0);
  }
  if((n = write(fd, buf, MAX)) != MAX){
    printf("Write failed!\n");
    test_failed();
  }
  close(fd);
  
  //read
  if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE | O_RDWR)) < 0){
    printf("Failed to open the small file\n");
    test_failed();
  }
  for(i = 0; i < MAX; i++) {
    if((n = read(fd, &buf2[i], 1)) != 1){
      printf("Read failed! %d\n", n);
      test_failed();
    }
    
    if(buf[i] != buf2[i]){
      printf("Data mismatch.\n");
      test_failed();
    }
  }
  close(fd);

  test_passed();
	exit(0);
}
