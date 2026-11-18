#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void exception_hanlder(int a) {
    printf("Acceso ilegal a memoria\n");
    exit(0);
}

int main() {
    int *ptr = NULL;
    signal(SIGSEGV, exception_hanlder);
    *ptr = 10;
    return 0;
}
