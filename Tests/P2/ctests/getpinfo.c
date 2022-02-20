#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"
#include <stddef.h>

#define check(exp, msg) if(exp) {} else {\
   printf("%s:%d check (" #exp ") failed: %s\n", __FILE__, __LINE__, msg);\
   exit(-1);}

int
main(int argc, char *argv[])
{
   struct pstat st;

   check(getpinfo(&st) == 0, "getpinfo");
   printf("\n **** PInfo **** \n");
   int i;
   for(i = 0; i < NPROC; i++) {
      if (st.inuse[i]) {
         printf("pid: %d hticks: %d lticks: %d\n", st.pid[i], st.hticks[i], st.lticks[i]);
      }
   }

   check(getpinfo(NULL) == -1, "getpinfo with bad pointer");
  // printf("Process1 Done\n");
  // printf("Process2 Done\n");
  // printf("Process1 Done\nProcess2 Done\n");
  printf("Should print 1 then 2");
  exit(0);
}
