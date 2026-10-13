#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t p = fork();
    if(p<0)
    {
      perror("Error haciendo fork().");
      exit(1);
    }
    else if ( p == 0) printf("Proceso hijo!\n");
    else printf("Proceso padre!\n");
    return 0;
}

