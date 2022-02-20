/* check that address space size is updated in threads */
#include "kernel/types.h"
#include "user/user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

int ppid;
int global = 0;
unsigned int size = 0;
lock_t lock, lock2;
int num_threads = 30;


#define assert(x) if (x) {} else { \
   printf("%s: %d ", __FILE__, __LINE__); \
   printf("assert failed (%s)\n", # x); \
   printf("TEST FAILED\n"); \
   kill(ppid); \
   exit(0); \
}

void worker(void *arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();

   int arg = 101;
   void *arg_ptr = &arg;

   lock_init(&lock);
   lock_init(&lock2);
   lock_acquire(&lock);
   lock_acquire(&lock2);

   int i;
   for (i = 0; i < num_threads; i++) {
      int thread_pid = thread_create(worker, arg_ptr);
      assert(thread_pid > 0);
   }

   size = (uint64)sbrk(0);

   while (global < num_threads) {
      lock_release(&lock);
      sleep(100);
      lock_acquire(&lock);
   }

   global = 0;
   sbrk(10000);
   size = (uint64)sbrk(0);
   lock_release(&lock);

   while (global < num_threads) {
      lock_release(&lock2);
      sleep(100);
      lock_acquire(&lock2);
   }
   lock_release(&lock2);


   for (i = 0; i < num_threads; i++) {
      int join_pid = thread_join();
      assert(join_pid > 0);
   }

   printf("TEST PASSED\n");
   exit(0);
}

void
worker(void *arg_ptr) {
   lock_acquire(&lock);
   assert((uint64)sbrk(0) == size);
   global++;
   lock_release(&lock);

   lock_acquire(&lock2);
   assert((uint64)sbrk(0) == size);
   global++;
   lock_release(&lock2);

   exit(0);
}

