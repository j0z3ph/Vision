#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void signalHandler(int sig);

int main()
{
    if (signal(SIGINT, signalHandler) == SIG_ERR)
    {
        perror("Upsss!\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("Hola\n");
        sleep(1);
    }

    return 0;
}

void signalHandler(int sig)
{
    printf(" [SIGINT] Atrapado. Adios...\n");
    exit(sig);
}