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
  char buf[MAX];
  char buf2[MAX];
  char buf3[MAX];

  for(i = 0; i < MAX; i++){
    buf[i] = (char)(i+(int)'0');
  }
  
  for(i = 0; i < MAX; i++){
    buf2[i] = (char)(i-(int)'0');
  }
  
  
  //create
  if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE)) < 0){
    printf("Failed to create a small file\n");
    test_failed();
  }
  close(fd);
  
  
  //write
  if((fd = open("test_file.txt", O_RDWR)) < 0){
    printf("Failed to open a small file\n");
    test_failed();
  }
 
  if(write(fd, buf, MAX) != MAX){
    printf("Write failed!\n");
    test_failed();
  }
  close(fd);
  
  
  //write with O_RDONLY flag
  if((fd = open("test_file.txt", O_RDONLY)) < 0){
    printf("Failed to open a small file as read only\n");
    test_failed();
  }
  
  if(write(fd, buf2, MAX) >= 0){ //tries to overwrite data with new data
    printf("Write succeeded despite O_RDONLY flag!\n");
    test_failed();
  }
  close(fd);

  
  //read
  if((fd = open("test_file.txt", O_RDONLY)) < 0){
    printf("Failed to open a small file as read only\n");
    test_failed();
  }
  
  if(read(fd, buf3, MAX) != MAX){
    printf("Read failed!\n");
    test_failed();
  }
  close(fd);
  
  for(i = 0; i < MAX; i++){
    if(buf[i] != buf3[i]){
      printf("Data mismatch, possibly because second write succeeded despite O_RDONLY flag\n");
      test_failed();
    }
  }
  
  test_passed();
	exit(0);
}
