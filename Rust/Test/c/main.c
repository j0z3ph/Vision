#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    size_t *arr = malloc(sizeof(size_t));
    size_t _size;
    size_t aux;
    int found = 0;
    clock_t start, end;
    double elapsed;

    printf("Number of tests: ");
    scanf("%lu", &_size);

    start = clock();
    for (size_t i = 0; i < _size; i++)
    {
        arr = realloc(arr, sizeof(size_t) * (i + 1));
        arr[i] = rand() % _size;
    }
    end = clock();
    elapsed = (double)(end - start) / (double)(CLOCKS_PER_SEC / 1000);
    printf("%lf\n", elapsed);

    // Busqueda:

    for (size_t i = 0; i < 50; i++)
    {
        aux = rand() % _size;
        found = 0;
        start = clock();
        for (size_t i = 0; i < _size; i++)
        {
            if (arr[i] == aux)
            {
                end = clock();
                elapsed = (double)(end - start) / (double)(CLOCKS_PER_SEC / 1000);
                printf("Found (%ld). Elapsed: %lf ms.\n", aux, elapsed);
                found = 1;
                break;
            }
        }
        if (!found)
        {
            end = clock();
            elapsed = (double)(end - start) / (double)(CLOCKS_PER_SEC / 1000);
            printf("NOT Found (%ld). Elapsed: %lf\n", aux, elapsed);
        }
    }

    return 0;
}
