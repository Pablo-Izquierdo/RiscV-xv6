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
  
  if((n = write(fd, buf, MAX)) != MAX){
    printf("Write failed!\n");
    test_failed();
  }
  printf("bytes written = %d\n", n);
  close(fd);
  
  if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE | O_RDWR)) < 0){
    printf("Failed to open the small file\n");
    test_failed();
  }
  
  if((n = read(fd, buf2, MAX*2)) != MAX){
    printf("Read failed! : %d\n", n);
    test_failed();
  }
  printf("bytes read = %d\n", n);
  close(fd);

  /*for (int i=0; i<MAX*2; i++)
      printf("%c ,%c\n", buf[i], buf2[i]);*/
  
  for(i = 0; i < MAX; i++){
    if(buf[i] != buf2[i]){
      printf("Data mismatch.\n");
      test_failed();
    }
    //printf("%d : %c ,%c\n", i, buf[i], buf2[i]);
  }
  
  test_passed();
	exit(0);
}
