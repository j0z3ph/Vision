#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

// Manejador para la señal SIGINT
void signalHandler(int sig);

int main(void)
{
    if (signal(SIGINT, signalHandler) == SIG_ERR)
    {
        perror("Upsss!\n");
        exit(EXIT_FAILURE);
    }


    printf("Enviando señal SIGINT a mi mismo...");
    if (raise(SIGINT) != 0)
    {
        perror("Error al enviar la señal");
        return 1;
    }

    printf("Programa finalizado correctamente.\n");
    return 0;
}

void signalHandler(int sig)
{
    printf("\nSeñal capturada: %d (%s)\n", sig, strsignal(sig));
}

