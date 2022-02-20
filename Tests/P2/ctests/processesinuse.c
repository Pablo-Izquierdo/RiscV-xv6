#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"
#define check(exp, msg) if(exp) {} else {\
   printf("%s:%d check (" #exp ") failed: %s\n", __FILE__, __LINE__, msg);\
   exit(-1);}
#define PROC 7

int spin()
{
	int i = 0, j = 0;
	while(1)
	for(j = 0; j < 10000000;++j)
	{
		i = j % 11;
	}
	j=i;
   return i;
}
int
main(int argc, char *argv[])
{
   struct pstat st;
   int count = 0;
   int i = 0;
   int *aux = malloc(1*sizeof(int));
   int pid[NPROC];
   while(i < PROC)
   {
        pid[i] = fork();
	if(pid[i] == 0)
        {
		aux[0] += spin();
		exit(0);
        }
	i++;
   }
   sleep(500);
   check(getpinfo(&st) == 0, "getpinfo");
   printf("\n**** PInfo ****\n");
   for(i = 0; i < NPROC; i++) {
      if (st.inuse[i]) {
	 count++;
         printf("pid: %d hticks: %d lticks: %d\n", st.pid[i], st.hticks[i], st.lticks[i]);
      }
   }
   for(i = 0; i < PROC; i++)
   {
	kill(pid[i]);
   }
   printf("Number of processes in use %d\n", count);
   check(count == 10, "getpinfo should return 10 processes in use\n");
   printf("Should print 1 then 2");
   exit(0);
}
