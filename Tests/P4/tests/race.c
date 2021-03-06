/* race condition in CV? (must atomically release lock and sleep) */
#include "kernel/types.h"
#include "user/user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

#define N 1
int ppid;
int pid1, pid2;
volatile int bufsize;
int result;
lock_t lock;
cond_t nonfull, nonempty;

#define assert(x) if (x) {} else { \
   printf("%s: %d ", __FILE__, __LINE__); \
   printf("assert failed (%s)\n", # x); \
   printf("TEST FAILED\n"); \
   kill(ppid); \
   exit(0); \
}

void produce(void *arg);
void consume(void *arg);

int
main(int argc, char *argv[])
{
  int i;
  ppid = getpid();

  lock_init(&lock);
  bufsize = 0;

  assert((pid1 = thread_create(produce, NULL)) > 0);
  assert((pid2 = thread_create(consume, NULL)) > 0);

  for(i = 0; i < 500; i++) {
    result <<= 1;
    sleep(1);
  }

  printf("%p\n", result);
  if(result & 0x3ff)
    printf("TEST PASSED\n");
  exit(0);
}

void
produce(void *arg) {
  while(1) {
    lock_acquire(&lock);
    while(bufsize == N)
      cv_wait(&nonfull, &lock);

    result <<= 1;
    result |= 1;

    bufsize++;
    cv_signal(&nonempty);
    lock_release(&lock);
  }
}

void
consume(void *arg) {
  while(1) {
    lock_acquire(&lock);
    while(bufsize == 0)
      cv_wait(&nonempty, &lock);

    result <<= 1;
    result |= 1;

    bufsize--;
    cv_signal(&nonfull);
    lock_release(&lock);
  }
}
