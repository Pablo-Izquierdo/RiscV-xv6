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

#define MAX 50

int
main(int argc, char *argv[])
{
  int fd, i;
  struct stat st;
  char buf[MAX];
  char buf2[MAX];

  for(i = 0; i < MAX; i++){
    buf[i] = (char)(i+(int)'0');
  }
  
  
  //create
  if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE)) < 0){
    printf("Failed to create a small file\n");
    test_failed();
  }
  close(fd);
  
  
  //type check and write
  if((fd = open("test_file.txt", O_RDWR)) < 0){
    printf("Failed to open a small file\n");
    test_failed();
  }
  
  if(fstat(fd, &st) < 0){
    printf("Failed to get stat on the small file\n");
    test_failed();
  }
  
  if (st.type != T_SMALLFILE) {
    printf("Did not create a small file\n");
    test_failed();
  }
 
  if(write(fd, buf, MAX) != MAX){
    printf("Write failed!\n");
    test_failed();
  }
  close(fd);

  
  //read
  if((fd = open("test_file.txt", O_RDWR)) < 0){
    printf("Failed to open a small file\n");
    test_failed();
  }
  
  if(read(fd, buf2, MAX) != MAX){
    printf("Read failed!\n");
    test_failed();
  }
  close(fd);
  
  for(i = 0; i < MAX; i++){
    if(buf[i] != buf2[i]){
      printf("Data mismatch.\n");
      test_failed();
    }
  }
  
  test_passed();
	exit(0);
}
