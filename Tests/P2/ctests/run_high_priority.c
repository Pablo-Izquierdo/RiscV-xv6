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
	for(i = 0; i < 10; ++i)
	{
		for(j = 0; j < 100000000; ++j)
		{
			k = j % 10;
		}
	}
	j=k;
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

void compare(struct pstat *before, struct pstat *after)
{
	int i, processesrun = 0;
	for(i = 0; i < NPROC; i++)
	{
		check(before->inuse[i] == after->inuse[i], "number of processes inuse viewed at different times should be same");
		check(before->pid[i] == after->pid[i], "the pid of processes at a particular index taken viewed at different times should be same");
		check(before->lticks[i] == after->lticks[i], "no low priority process should have been run when there is a runnable high priority process");
		if(before->hticks[i] < after->hticks[i])
			processesrun++;
	}
	check(processesrun == 1, "Expecetd that only the high prirority process is run when there is one");
}

int
main(int argc, char *argv[])
{
	int *aux = malloc(3*sizeof(int));
   if(fork() == 0)
   {
   	struct pstat st_before, st_after;
	check(setpri(2) == 0, "setpri");
	check(getpinfo(&st_before) == 0, "getpinfo");
	printf("\n ****PInfo before**** \n");
	print(&st_before);
	aux[0] += spin();
	aux[1] += spin();
	check(getpinfo(&st_after) == 0, "getpinfo");
	printf("\n ****PInfo after**** \n");
	print(&st_after);
	compare(&st_before, &st_after);
	printf("Should print 1"); 
	exit(0);
   }
   aux[2] += spin();
   printf(" then 2");
   exit(0);
}
