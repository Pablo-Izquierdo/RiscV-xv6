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
   int highpriority = 0;
   int processwithlowticks = 0;
   int i;
   int *aux = malloc(1*sizeof(int));
   check(setpri(2) == 0, "setpri");
   
   check(getpinfo(&st_before) == 0, "getpinfo");
   printf("\n **** PInfo Before**** \n");
   print(&st_before);

   aux[0] += spin();

   check(getpinfo(&st_after) == 0, "getpinfo");
   printf("\n **** PInfo After**** \n");
   print(&st_after);
   
   for(i = 0; i < NPROC; i++) {
      if (st_before.inuse[i] && st_after.inuse[i]) {
	 if(st_before.lticks[i] != st_after.lticks[i])
	 {
		processwithlowticks++;
	 } 
	 if(st_after.hticks[i] - st_before.hticks[i] > 0)
		highpriority++;
      }
   }
   check(processwithlowticks == 0, "low ticks shouldn't have been increased for any of the processes");
   check(highpriority == 1, "getpinfo should return 1 process with hticks greater than 0");
   printf("Should print 1 then 2");
   exit(0);
}
