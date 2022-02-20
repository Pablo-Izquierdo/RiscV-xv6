
#include "../kernel/types.h"
#include "../kernel/pstat.h"
#include "user.h"

int main (void){

    struct pstat *pstat = malloc(sizeof(struct pstat));
    int count = 1;
    int limit = 15;
    getpinfo(pstat);
    printf ("LOW PRIORITY\n");
    printf ("RUNNIG    PID    Hticks    Lticks\n");
    for (int i = 0; i < NPROC; i++){
        if(count == limit && pstat->pid[i] != 0) limit ++;
        printf ("  %d       %d      %d        %d\n", pstat->inuse[i], pstat->pid[i], pstat->hticks[i], pstat->lticks[i]);
        if(count == limit || count == NPROC){
            break;
        } 
        count++;
    }




    setpri(2);
    for (int i =0; i< 10000000; i++); //high priority
    free(pstat);
    pstat = malloc(sizeof(struct pstat));
    getpinfo(pstat);

    printf ("SHOW EFFECT OF LOW PRIORITY AND CHANGE TO HIGH PRIORITY\n");
    printf ("RUNNIG    PID    Hticks    Lticks\n");
    count = 1;
    for (int i = 0; i < NPROC; i++){
        if(count == limit && pstat->pid[i] != 0) limit ++;
        printf ("  %d       %d      %d        %d\n", pstat->inuse[i], pstat->pid[i], pstat->hticks[i], pstat->lticks[i]);
        if(count == limit || count == NPROC){
            break;
        } 
        count++;
    }



    setpri(1);
    free(pstat);
    pstat = malloc(sizeof(struct pstat));
    getpinfo(pstat);
    printf("SHOW EFFECT OF HIGH PRIORITY AND CHANGE TO LOW PRIORITY\n");
    printf ("RUNNIG    PID    Hticks    Lticks\n");
    count = 1;
    for (int i = 0; i < NPROC; i++){
        if(count == limit && pstat->pid[i] != 0) limit ++;
        printf ("  %d       %d      %d        %d\n", pstat->inuse[i], pstat->pid[i], pstat->hticks[i], pstat->lticks[i]);
        if(count == limit || count == NPROC){
            break;
        } 
        count++;
    }



    free(pstat);
    pstat = malloc(sizeof(struct pstat));
    getpinfo(pstat);
    printf ("LOW PRIORITY\n");
    printf ("RUNNIG    PID    Hticks    Lticks\n");
    count = 1;
    for (int i = 0; i < NPROC; i++){
        if(count == limit && pstat->pid[i] != 0) limit ++;
        printf ("  %d       %d      %d        %d\n", pstat->inuse[i], pstat->pid[i], pstat->hticks[i], pstat->lticks[i]);
        if(count == limit || count == NPROC){
            break;
        } 
        count++;
    }

    free(pstat);
    exit(0);
}

