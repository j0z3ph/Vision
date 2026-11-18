#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int sig) {
    printf("\nTiempo agotado. Señal recibida: %d\n", sig);
    fclose(stdin); // Manda EOF a scanf
}

int main() {
    int numero;
    signal(SIGALRM, alarm_handler);

    printf("Tienes 5 segundos para ingresar un número: ");
    //fflush(stdout); // Asegura que el texto se imprima antes del scanf (funcion bloqueante)

    alarm(5);

    if (scanf("%d", &numero) == 1) {
        alarm(0); // Cancela la alarma
        printf("Ingresaste el número: %d\n", numero);
    }

    printf("Adios\n");

    return 0;
}
