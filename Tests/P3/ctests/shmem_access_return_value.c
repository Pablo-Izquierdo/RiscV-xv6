#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "stddef.h"
#include "kernel/param.h"
#include "kernel/riscv.h"
#include "kernel/memlayout.h"

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
  void *ptr;

	ptr = shmem_access(2);
	if (ptr == NULL) {
		test_failed();
	}

	if (((long int) ptr) != TRAPFRAME - PGSIZE*1) {
		test_failed();
	}

	ptr = shmem_access(3);
	if (ptr == NULL) {
		test_failed();
	}

	if (((long int) ptr) != TRAPFRAME - PGSIZE*2) {
		test_failed();
	}

	ptr = shmem_access(0);
	if (ptr == NULL) {
		test_failed();
	}

	if (((long int) ptr) != TRAPFRAME - PGSIZE*3) {
		test_failed();
	}

	ptr = shmem_access(1);
	if (ptr == NULL) {
		test_failed();
	}

	if (((long int) ptr) != TRAPFRAME - PGSIZE*4) {
		test_failed();
	}
	
	test_passed();
	exit(0);
}
