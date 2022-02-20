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

#define MAX 50

int
main(int argc, char *argv[])
{
  int fd, i;
  char buf[MAX]; //data out
  char buf2[MAX]; //data in
  char buf3[MAX]; //data in
  
  char buf_unchanged[MAX]; //this data should never be changed throughout this program once initialized

  for(i = 0; i < MAX; i++){
    buf[i] = (char)(i+(int)'0');
  }
  
  for(i = 0; i < MAX; i++){
    buf_unchanged[i] = (char)(i-(int)'0');
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
  
  
  //read to make sure normal write succeeded
  if((fd = open("test_file.txt", O_RDONLY)) < 0){
    printf("Failed to open a small file as read only\n");
    test_failed();
  }
  
  if(read(fd, buf2, MAX) != MAX){
    printf("Read failed!\n");
    test_failed();
  }
  close(fd);
  
  for(i = 0; i < MAX; i++){
    if(buf[i] != buf2[i]){
      printf("Data mismatch\n");
      test_failed();
    }
  }
  
  
  //read with O_WRONLY flag
  if((fd = open("test_file.txt", O_WRONLY)) < 0){
    printf("Failed to open a small file as write only\n");
    test_failed();
  }
  
  if(read(fd, buf_unchanged, MAX) >= 0){ //MAIN TEST
    printf("Read succeeded despite O_WRONLY flag!\n");
    test_failed();
  }
  close(fd);
  
  for(i = 0; i < MAX; i++){
    if(buf_unchanged[i] != (char)(i-(int)'0')){
      printf("Failed read system call modified buffer passed in!\n");
      test_failed();
    }
  }
  
  
  //read to make sure normal write is still persisted correctly, in case read with O_WRONLY somehow corrupted data
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
      printf("Data mismatch\n");
      test_failed();
    }
  }
  
  test_passed();
	exit(0);
}
