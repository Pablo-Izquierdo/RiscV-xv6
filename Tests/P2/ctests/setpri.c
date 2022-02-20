#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"

#define check(exp, msg) if(exp) {} else {\
   printf("%s:%d check (" #exp ") failed: %s\n", __FILE__, __LINE__, msg);\
   exit(-1);}

int
main(int argc, char *argv[])
{
   check(setpri(1) == 0, "setpri to 1");
   check(setpri(2) == 0, "setpri to 2");
   check(setpri(-1) == -1, "setpri to <0");
   check(setpri(10) == -1, "setpri to 10");
   printf("Should print 1 then 2");
   exit(0);
}
