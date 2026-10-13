#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int x = 1;
    pid_t p = fork();
    if (p < 0)
    {
        perror("Upssss!");
        exit(1);
    }
    else if (p == 0) printf("Valor de x en proceso hijo: %d\n", ++x);
    else printf("Valor de x en proceso padre: %d\n", --x);
    
    return 0;
}

