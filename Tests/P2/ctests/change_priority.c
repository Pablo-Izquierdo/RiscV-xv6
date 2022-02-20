#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"
#define check(exp, msg) if(exp) {} else {\
   printf("%s:%d check (" #exp ") failed: %s\n", __FILE__, __LINE__, msg);\
   exit(-1);}

int spin()
{
	int i = 0, j = 0, k = 0;
	for(i = 0; i < 50; ++i)
	{
		for(j = 0; j < 10000000; ++j)
		{
			k = j % 10;
		}
	}
	i=k;
   return k;
}

void print(struct pstat *st)
{
   int i;
   for(i = 0; i < NPROC; i++) {
      if (st->inuse[i]) {
         printf("pid: %d hticks: %d lticks: %d\n", st->pid[i], st->hticks[i], st->lticks[i]);
      }
   }

}


int
main(int argc, char *argv[])
{
 
   struct pstat st_before, st_after;
   int pid = getpid();
   int lowpriorityrun = 0;
   int  highpriorityrun = 0;
   int i;
   int *aux = malloc(2*sizeof(int));
   check(setpri(2) == 0, "setpri");
   // check if process run in high priority mode once set to high
  
   check(getpinfo(&st_before) == 0, "getpinfo");
   printf("\n ****PInfo before**** \n");
   print(&st_before);
   aux[0] += spin();
   check(getpinfo(&st_after) == 0, "getpinfo");
   printf("\n ****PInfo after**** \n");
   print(&st_after);
   for(i = 0; i < NPROC; ++i)
   {
	if(st_before.pid[i] == pid && st_after.pid[i] == pid)
	{
		if(st_before.hticks[i] < st_after.hticks[i] && st_before.lticks[i] == st_after.lticks[i])
			highpriorityrun = 1;
	}		
   }
   check(highpriorityrun == 1, "Expected process to have run in high priority mode once priority changed to high");

   check(setpri(1) == 0, "setpri");
 
  // check if process run in low priority mode once changed back
   check(getpinfo(&st_before) == 0, "getpinfo");
   printf("\n ****PInfo before**** \n");
   print(&st_before);
   aux[1] += spin();
   check(getpinfo(&st_after) == 0, "getpinfo");
   printf("\n ****PInfo after**** \n");
   print(&st_after);
   for(i = 0; i < NPROC; ++i)
   {
	if(st_before.pid[i] == pid && st_after.pid[i] == pid)
	{
		if(st_before.lticks[i] < st_after.lticks[i] && st_before.hticks[i] == st_after.hticks[i])
			lowpriorityrun = 1;
	}		
   }
   check(lowpriorityrun == 1, "Expected process to have run in low priority mode once priority changed back to low");
   printf("Should print 1 then 2"); 
   exit(0);
}
