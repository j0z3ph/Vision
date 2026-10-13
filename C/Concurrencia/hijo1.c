#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // argv[0] es el nombre del programa
    // argv[1] es el total de procesos hijos
    int total_hermanos = atoi(argv[1]);

    printf("Soy %ld y tengo %d hermanos!... ", 
        (long)getpid(), total_hermanos);
    sleep(10);
    printf("Proceso %ld terminado!\n", (long)getpid());

    return 0;
}

