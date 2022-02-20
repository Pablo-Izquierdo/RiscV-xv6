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

#define NBLOCKS (NDIRECT+1)
#define SIZE NBLOCKS*4

#define SMALLWRITE  10
#define BIGWRITE    100

int
main(int argc, char *argv[])
{
  int fd, i;
  char buf[SMALLWRITE + BIGWRITE];
  char buf2[SMALLWRITE + BIGWRITE];
  struct stat st;
  
  for(i = 0; i < SIZE; i++){
    buf[i] = (char)(i+(int)'0');
  }
  memset(buf2, 0, SIZE);
  
  //writes
  if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE | O_RDWR)) < 0){
    printf("Failed to create the small file\n");
    test_failed();
  }
  int a;
  if(write(fd, buf, SMALLWRITE) != SMALLWRITE){
    printf("Failed to do a small write\n");
    test_failed();
  }
  
  if((a=write(fd, buf+SMALLWRITE, BIGWRITE)) != SIZE-SMALLWRITE){
    printf("Failed to do a truncated big write %d\n",a);
    test_failed();
  }
  close(fd);
  
  //read
  if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE | O_RDWR)) < 0){
    printf("Failed to open the small file\n");
    test_failed();
  }
  
  if(fstat(fd, &st) < 0){
    printf("Failed to get stat on the small file\n");
    test_failed();
  }
  
  if(st.size != SIZE){
    printf("Invalid file size. %d %d\n", st.size, SIZE);
    test_failed();
  }
  
  if(read(fd, buf2, SIZE) != SIZE){
    printf("Read failed!\n");
    test_failed();
  }
  close(fd);
  
  for(i = 0; i < SIZE; i++){
    if(buf[i] != buf2[i]){
      printf("Data mismatch.\n");
      test_failed();
    }
  }
  
  test_passed();
	exit(0);
}
