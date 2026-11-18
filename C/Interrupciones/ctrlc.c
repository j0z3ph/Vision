#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>



void exception_hanlder(int a)
{
    static int intcont = 0;
    printf("Ctr+C detectado. Numero de intentos: %i\n", ++intcont);
    if(intcont == 5) exit(1);
}

int main()
{
    int contador = 0;
    signal(SIGINT, exception_hanlder);

    printf("Para finalizar el programa debera presionar Ctr+C cinco veces.\n");

    while(1)
    {
        printf("Contador: %i\n", ++contador);
        sleep(1);
    }

    return 0;
}
