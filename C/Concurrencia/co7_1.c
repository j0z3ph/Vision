#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h> // #include <wait.h>

#define NUM_HIJOS 5

int main(int argc, char *argv[])
{
    pid_t pids[NUM_HIJOS];
    int i, exit_status;
    char num_hijos_str[4];
    sprintf(num_hijos_str, "%d", NUM_HIJOS);

    for (i = 0; i < NUM_HIJOS; i++)
    {
        pids[i] = fork();
        if (pids[i] == 0)
        {
            // Proceso hijo
            // Reemplazamos el codigo del fork por un nuevo programa
            execl("./hijo1", "hijo1", num_hijos_str, NULL);
        }
    }

    for (i = 0; i < NUM_HIJOS; i++)
    {
        waitpid(pids[i], &exit_status, 0);
        if (WIFEXITED(exit_status))
            printf("Proceso %ld finalizado con estatus %d.\n", 
                (long)pids[i], WEXITSTATUS(exit_status));
        else
            printf("Proceso %ld finalizado de forma anormal.\n", 
                (long)pids[i]);
    }

    return EXIT_SUCCESS;
}

