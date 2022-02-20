#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int ppid = getpid();

  int pid = fork();
	if (pid < 0) {
		printf("TEST FAILED\n");
		exit(0);
	}  
	else if (pid == 0) {
  	uint * badp = (uint*)4095;
    printf("bad dereference (0x0fff): ");
    printf("%x %x\n", badp, *badp);
    // this process should be killed
    printf("TEST FAILED\n");
    kill(ppid);
    exit(0);
  }
	else {
  	wait(0);
  }

  printf("TEST PASSED\n");
  exit(0);
}
