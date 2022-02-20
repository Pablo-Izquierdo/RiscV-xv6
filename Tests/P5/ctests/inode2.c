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

#define NINODES 200
#define STRIDE 9

int
main(int argc, char *argv[])
{
  int fd, i, pid;
  struct stat st;
  int latest_inode;
  
  char filename[2] = {'0', '\0'};
  
  //creating a file to get the latest inode number
  if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE)) < 0){
    printf("Failed to create a small file\n");
    test_failed();
    exit(0);
  }
  if(fstat(fd, &st) < 0){
    close(fd);
    printf("Failed to get stat on the small file\n");
    test_failed();
    exit(0);
  }
  close(fd);
  
  latest_inode = st.ino;
  printf("latest_inode = %d\n", latest_inode);
  
  for(i = latest_inode+1; i < NINODES; i++){
    printf("creating file at inode %d\n", i);
    if((fd = open(filename, O_CREATE | O_SMALLFILE)) < 0){
      printf("Failed to create a small file\n");
      test_failed();
    }
    if(fstat(fd, &st) < 0){
      printf("Failed to get stat on the small file\n");
      test_failed();
    }
    
    if(st.ino != i){
      printf("ERROR! inodes were not allocated in order\n");
      test_failed();
    }
    
    close(fd);
    filename[0]++;
  }
  
  printf("used up all inodes\n");
  
  filename[0] = '0'; //reset filename
  
  //delete files
  for(i = latest_inode+1+STRIDE; i < NINODES; i += STRIDE){
    printf("deleting file at inode %d\n", i);
    filename[0] += STRIDE;
    
    pid = fork();
    if(pid < 0){
      printf("Fork failed\n");
      test_failed();
    }
    else if(pid == 0) {
      char *args[3] = {"rm", filename, 0};
      exec(args[0], args);
      printf("exec failed!\n");
      test_failed();
    }
    else {
      wait(0);
    }
  }
  
  filename[0] = '0'; //reset filename
  
  //try to open just-deleted files, but they should fail
  for(i = latest_inode+1+STRIDE; i < NINODES; i += STRIDE){
    printf("testing existence of file at inode %d\n", i);
    filename[0] += STRIDE;
    
    if((fd = open(filename, O_RDWR)) >= 0){
      printf("Opened small file that should have been deleted\n");
      test_failed();
    }
  }
  
  filename[0] = '0'; //reset filename
  
  //create small files again and make sure it allocates the first inode available
  for(i = latest_inode+1+STRIDE; i < NINODES; i += STRIDE){
    printf("recreating file at inode %d\n", i);
    filename[0] += STRIDE;
    
    if((fd = open(filename, O_CREATE | O_SMALLFILE | O_RDWR)) < 0){
      printf("Failed to create a small file\n");
      test_failed();
    }
    
    if(fstat(fd, &st) < 0){
      printf("Failed to get stat on the small file\n");
      test_failed();
    }
    
    if(st.ino != i){
      printf("Failed to allocate small file at the right inode; allocated at inode %d, but inode %d should have been used\n", st.ino, i);
      test_failed();
    }
    
    close(fd);
  }

  test_passed();
	exit(0);
}
