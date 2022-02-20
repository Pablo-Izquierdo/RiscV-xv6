#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
#include "kernel/riscv.h"
#include "stddef.h"

#define PGSIZE 4096

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

int
main(int argc, char *argv[])
{
 	char *ptr = (char *)(MAXVA - 4096);
  *ptr = 'c';
	test_failed();
	exit(0);
}
