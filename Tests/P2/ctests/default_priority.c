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
		for(j = 0; j < 100000000; j++)
			k = j % 11;
	}
	i=k;
   return k;
}
int
main(int argc, char *argv[])
{
   struct pstat st;
   int highpriority = 0;
   int pid = getpid();
   int defaultpriorityrun = 0;
   int *aux = malloc(2*sizeof(int));
   aux[0] += spin();
   check(getpinfo(&st) == 0, "getpinfo");

   int i;
   printf("\n **** PInfo **** \n"); 
   for(i = 0; i < NPROC; i++) {
      if (st.inuse[i]) {
	 if(st.hticks[i] != 0)
		highpriority++;
	 if(st.pid[i] == pid && st.lticks[i] > 20)
		defaultpriorityrun = 1;
         printf("pid: %d hticks: %d lticks: %d\n", st.pid[i], st.hticks[i], st.lticks[i]);
      }
   }

   check(highpriority == 0, "getpinfo shouldn't return any process with hticks not equal to 0, default priority should be low(1) ");
   check(defaultpriorityrun == 1, "getpinfo should return a process having run with default priority");
   printf("Should print 1 then 2");
   exit(0);
}
