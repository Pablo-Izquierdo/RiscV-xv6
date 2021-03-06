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

int
main(int argc, char *argv[])
{
  int fd, i;
  char buf[SIZE];
  char buf2[SIZE];
  char tmp;
  struct stat st;
  
  for(i = 0; i < SIZE; i++){
    buf[i] = (char)(i+(int)'0');
  }
  memset(buf2, 0, SIZE);
  
  //open, write 1 byte to the end, close
  for(i = 0; i < SIZE+5; i++){
    if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE | O_RDWR)) < 0){
      printf("Failed to create the small file\n");
      test_failed();
    }
    
    while(read(fd, &tmp, 1) == 1) { } //go to end of file
    
    if((write(fd, &buf[i], 1)) != 1){
      printf("a :%d\n", i); //ROMPE EN i =1 porque? -> write devuelve -1
      break;
    }
    close(fd);
  }
  
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
    printf("Invalid file size. %d, %d\n", st.size, SIZE);
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
