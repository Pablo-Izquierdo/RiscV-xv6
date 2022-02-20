#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "stddef.h"
#include "math.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;
  struct proc* p=myproc();

  if(argint(0, &n) < 0)
    return -1;

  addr = p->sz;

  if((p->asid == p->pid) && (p->mythreads == 0 && p->soythread == 0)){ //normal execution
    if(growproc(n) < 0)
      return -1;

  } else if (n > 0){ //  when you share the address space
    printf("incrementando threads\n");
    struct proc* asidOwner;
    if(p->pid != p->asid){ // I am not the Owner of address space
      if((asidOwner=findAsidOwner(p->asid)) == NULL){
        printf("Error: asidOwner not find");
        return -1;
      }
    }else{
      asidOwner=p;
    }
    addr = asidOwner->sz;
    if(growdifferentproc(n, asidOwner) < 0)
      return -1;

    if(findgrowthread(n, asidOwner, addr)< 0)
      return -1;
  }

  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_clone(void) //.ADD
{
  uint64 stack;
  uint64 arg;
  uint64 fcn;

   //obtenemos puntero función
   if(argaddr(0, &fcn) < 0){
     return -1;
   }

   //obtenemos puntero a argumento de función
   if(argaddr(1, &arg) < 0){
     return -1;
   }

   //obtenemos putnero a stack de usuario
   if(argaddr(2, &stack) < 0){
     return -1;
   }

   //Check Errors 
    uint64 sz = myproc()->sz;

   if(stack % PGSIZE != 0 || (sz - (uint64)stack) < PGSIZE){
     return -1;
   }

  return clone((void *)fcn, (void *)arg, (void *)stack);

}


uint64
sys_join(void) //.ADD
{
  uint64 stack;

  if(argaddr(0, &stack) < 0){
     return -1;
   }

   if(stack % 4 != 0 || myproc()->mythreads == 0){
     return -1;
   }
  
  return (uint64)join(stack);
}
