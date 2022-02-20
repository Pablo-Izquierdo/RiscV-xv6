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

#define MAX 25

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
  
  if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE | O_RDWR)) < 0){
    printf("Failed to create the small file\n");
    test_failed();
    exit(0);
  }
  
  if((n = write(fd, buf, MAX)) < 0){
    printf(1, "Write failed!\n");
    test_failed();
  }
  printf("bytes written = %d\n", n);
  close(fd);
  
  if(n != MAX){
    printf("Failed to write the right amount to the small file.\n");
    test_failed();
  }
  
  if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE | O_RDWR)) < 0){
    printf("Failed to create the small file\n");
    test_failed();
  }
  
  if((n = read(fd, buf2, MAX)) < 0){
    printf("Read failed!\n");
    test_failed();
  }
  printf("bytes read = %d\n", n);
  close(fd);
  
  if(n != MAX){
    printf("Failed to read the right amount to the small file.\n");
    test_failed();
  }
  
  for(i = 0; i < MAX; i++){
    if(buf[i] != buf2[i]){
      printf("Data mismatch.\n");
      test_failed();
    }
  }
  
  test_passed();
	exit(0);
}
