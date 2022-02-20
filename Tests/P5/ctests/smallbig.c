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

#define SMALLSIZE 25
#define BIGSIZE   500
#define NFILES    5
#define NBIGITERATIONS  5

int
main(int argc, char *argv[])
{
  int fd, i, j, k;
  char buf[SMALLSIZE];
  char buf2[SMALLSIZE];
  char buf3[BIGSIZE];
  char buf4[BIGSIZE];
  struct stat st;
  
  for(i = 0; i < SMALLSIZE; i++){
    buf[i] = (char)(i+(int)'0');
  }
  
  for(i = 0; i < BIGSIZE; i++){
    buf3[i] = (char)(i+10+(int)'0');
  }
  
  char filename[2] = {'0', '\0'};
  
  //create small files
  for(i = 0; i < NFILES; i++){
    if((fd = open(filename, O_CREATE | O_SMALLFILE | O_RDWR)) < 0){
      printf("Failed to create the small file\n");
      test_failed();
      exit(0);
    }
    
    if(write(fd, buf, SMALLSIZE) != SMALLSIZE){
      printf("Write failed!\n");
      test_failed();
    }
    close(fd);
    
    if((fd = open(filename, O_RDWR)) < 0){
      printf("Failed to open the small file\n");
      test_failed();
    }
    
    if(read(fd, buf2, SMALLSIZE) != SMALLSIZE){
      printf("Read failed!\n");
      test_failed();
    }
    close(fd);
    
    for(j = 0; j < SMALLSIZE; j++){
      if(buf[j] != buf2[j]){
        printf("Data mismatch.\n");
        test_failed();
      }
    }
    
    filename[0]++;
  }
  
  //create big files
  for(i = 0; i < NFILES; i++){
    if((fd = open(filename, O_CREATE | O_RDWR)) < 0){
      printf("Failed to create the normal file\n");
      test_failed();
      exit(0);
    }
    for(k = 0; k < NBIGITERATIONS; k++){
      if(write(fd, buf3, BIGSIZE) != BIGSIZE){
        printf("Write failed!\n");
        test_failed();
      }
    }
    close(fd);
    
    if((fd = open(filename, O_RDWR)) < 0){
      printf("Failed to open the normal file\n");
      test_failed();
    }
    for(k = 0; k < NBIGITERATIONS; k++){
      if(read(fd, buf4, BIGSIZE) != BIGSIZE){
        printf("Read failed!\n");
        test_failed();
      }
      for(j = 0; j < BIGSIZE; j++){
        if(buf3[j] != buf4[j]){
          printf("Data mismatch.\n");
          test_failed();
        }
      }
      memset(buf4, 0, BIGSIZE); //reset in buffer
    }
    close(fd);
    
    filename[0]++;
  }
  
  filename[0] = '0'; //reset filename
  
  //check file sizes
  for(i = 0; i < NFILES*2; i++){
    if((fd = open(filename, O_RDWR)) < 0){
      printf("Failed to open the file\n");
      test_failed();
    }

    if(fstat(fd, &st) < 0){
      printf("Failed to get stat on the file\n");
      test_failed();
    }
    
    if(i < NFILES && st.size != SMALLSIZE){ //small file
      printf("Small file does not have the right size %d %d %d\n", st.size, st.type, i);
      test_failed();
    }
    else if (i >= NFILES && st.size != BIGSIZE*NBIGITERATIONS){ //normal file
      printf("Normal file does not have the right size\n");
      test_failed();
    }
    
    close(fd);
    filename[0]++;
  }
  
  test_passed();
	exit(0);
}
