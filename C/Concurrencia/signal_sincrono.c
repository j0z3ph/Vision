#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void signalHandler(int sig);

int main()
{
    volatile int a = 1;
    volatile int b = 0;

    if (signal(SIGFPE, signalHandler) == SIG_ERR)
    {
        perror("Upsss!\n");
        exit(EXIT_FAILURE);
    }

    // Esto provocará un crash por SIGFPE
    int resultado = a / b;

    printf("Resultado: %d\n", resultado);

    return 0;
}

void signalHandler(int sig)
{
    printf("\nSeñal capturada: %d (%s)\n", sig, strsignal(sig));
    abort();
}

