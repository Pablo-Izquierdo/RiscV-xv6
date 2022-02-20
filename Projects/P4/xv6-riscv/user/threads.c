#include "kernel/types.h"
#include "user/user.h"
#include "stddef.h"

#define PAGESIZE 4096

extern void *malloc(uint);
extern void free(void *);

// Mutual exclusion lock.
typedef uint lock_t;
typedef uint cond_t;

int thread_create(void (*fcn)(void*), void* arg){

   void *stack = malloc(PAGESIZE);
   if(stack == NULL)
    printf("Error al allocatar memoria\n");
   if((uint64)stack % PAGESIZE)
     stack = stack + (4096 - (uint64)stack % PAGESIZE);

    return clone (fcn, arg, stack);

}

int thread_join(){

   void* stack;
   int threadId;
   if((threadId = join(&stack)) > 0 ){
       free(stack);
   }
    return threadId;

}

int lock_init(lock_t* t)
{
  t=0;
  return 0;
}

void lock_acquire(lock_t* t)
{

  
  // On RISC-V, sync_lock_test_and_set turns into an atomic swap:
  //   a5 = 1
  //   s1 = &lk->locked
  //   amoswap.w.aq a5, a5, (s1)
  while(__sync_lock_test_and_set(t, 1) != 0)
    sleep(1);
  //printf("Tomo lock %d\n", getpid());

  // Tell the C compiler and the processor to not move loads or stores
  // past this point, to ensure that the critical section's memory
  // references happen strictly after the lock is acquired.
  // On RISC-V, this emits a fence instruction.
  __sync_synchronize();
}

void lock_release(lock_t* t)
{
  //printf("Suelto lock %d\n", getpid());
  // Tell the C compiler and the CPU to not move loads or stores
  // past this point, to ensure that all the stores in the critical
  // section are visible to other CPUs before the lock is released,
  // and that loads in the critical section occur strictly before
  // the lock is released.
  // On RISC-V, this emits a fence instruction.
  __sync_synchronize();

  // Release the lock, equivalent to lk->locked = 0.
  // This code doesn't use a C assignment, since the C standard
  // implies that an assignment might be implemented with
  // multiple store instructions.
  // On RISC-V, sync_lock_release turns into an atomic swap:
  //   s1 = &lk->locked
  //   amoswap.w zero, zero, (s1)
  __sync_lock_release(t);

}

void cv_init(cond_t* cv){

  __sync_lock_test_and_set(cv, 0);
  
}

void cv_wait(cond_t *cv, lock_t *t){

  while(__sync_lock_test_and_set(cv, 0) != 1){
    //printf("durmiendo %d\n", getpid());
    lock_release(t);
    sleep(1);
    lock_acquire(t);
  }
  __sync_synchronize();
  //printf("Condicion %d se cumple %d\n", getpid());

}


void cv_signal(cond_t *cv){

  __sync_synchronize();
  __sync_lock_test_and_set(cv, 1);
  //printf("SEÑAL Condicion %d\n", getpid());

}
