#include "kernel/types.h"
#include "user/user.h"

int main (void){

    int numprocesos = getprocs();
    printf("El numero de procesos del sistema = %d\n", numprocesos);
    exit(0);
}