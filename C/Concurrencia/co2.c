#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int i = 1, n = 4;
    pid_t childpid;

    for (i = 1; i < n; i++)
    {
        childpid = fork();
        if (childpid > 0) // Código del padre.
            break;
    }

    printf("Proceso %ld con padre %ld\n", (long)getpid(), (long)getppid());

    //pause();

    return 0;
}

