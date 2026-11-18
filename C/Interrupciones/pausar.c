#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

bool flag = true;

void exception_hanlder(int a)
{
    flag = !flag;
    printf("Interrupcion\n");
}

int main()
{
    int contador = 0;
    signal(SIGUSR1, exception_hanlder);

    printf("Para finalizar el programa debera presionar Ctr+C.\n");

    while(1)
    {
        if(flag) printf("Contador: %i\n", ++contador);
        else printf("Conteo pausado.\n");
        sleep(1);
    }

    return 0;
}
