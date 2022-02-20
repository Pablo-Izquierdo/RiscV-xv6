#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"
#define check(exp, msg) if(exp) {} else {\
   printf("%s:%d check (" #exp ") failed: %s\n", __FILE__, __LINE__, msg);\
   exit(-1);}

int spin(void)
{
        int i = 0, j = 0, k = 0;
        for(i = 0; i < 50; ++i)
        {
                for(j = 0; j < 10000000; ++j)
                {
                    //printf("tu madre");
                        k = j % 10;   
                }
        }
        
        j=k;
        return k;
}


void main (void){
    //pid 3
    int rc = fork();
    struct pstat *pstat = malloc(sizeof(struct pstat));
    int rc1 = 0;
    int *aux = malloc(sizeof(11*sizeof(int)));

    if (rc==0){
        //pid 4
        setpri(2);
        aux += spin();
        rc1=fork();
        if(rc1){
            //pid5
            aux[10] += spin();     
            aux[9] += spin();
            exit(0);
        }
        aux[8] += spin();
        aux[7] += spin();
        printf("Be 1");
        exit(0);
    }
    getpinfo(pstat);
    //printf ("RUNNIG    PID    Hticks    Lticks\n");
    for(int i= 0; i<6; i++){
        aux[i] += spin();
        aux[i] += spin();
        aux[i] += 1;
        aux[i] += spin();
        //printf ("  %d       %d      %d        %d\n", pstat->inuse[i], pstat->pid[i], pstat->hticks[i], pstat->lticks[i]);
        aux[i] += spin();
    }
    printf("then 2");
    exit(0);



}