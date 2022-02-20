
#include "../kernel/types.h"
#include "../kernel/pstat.h"
#include "user.h"

int main (void){

    struct pstat *pstat = malloc(sizeof(struct pstat));
    getpinfo(pstat);

    printf ("RUNNIG    PID    Hticks    Lticks\n");
    for (int i = 0; i < NPROC; i++){
        printf ("  %d       %d      %d        %d\n", pstat->inuse[i], pstat->pid[i], pstat->hticks[i], pstat->lticks[i]);
    }
    free(pstat);
    exit(0);
}