/**
 * @file main.c
 * @author Jose Luis Cruz (jlcruz@ipn.mx)
 * @brief Arbol binario de busqueda
 * @version 0.1
 * @date 2025-05-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BST.h"

#define N 100000000

int main()
{
    BinarySearchTree *bst = newBST();
    Timer *timer = newTimer();
    int *arr = NULL, cont = 0, val, found;
    Node *res;

    srand(time(NULL));

    timer->start(&timer);

    for (size_t i = 0; i < N; i++)
    {
        bst->insert(&bst, rand() % N);
    }

    timer->stop(&timer);

    printf("%lf ms\n", timer->elapsedTime(&timer));

    timer->start(&timer);

    for (size_t i = 0; i < N; i++)
    {
        if (arr == NULL)
            arr = malloc(sizeof(int));
        else
            arr = realloc(arr, sizeof(int) * (cont + 1));
        arr[cont] = rand() % N;
        cont++;
    }

    timer->stop(&timer);

    printf("%lf ms\n", timer->elapsedTime(&timer));

    printf("Busquedas:\n");

    for (size_t i = 0; i < 50; i++)
    {
        timer->start(&timer);
        res = bst->search(bst, rand() % N);
        timer->stop(&timer);

        printf("%lf ms. ", timer->elapsedTime(&timer));

        if (res != NULL)
            printf("Encontrado (%i) en abb\n", res->value);
        else
            printf("No encontrado en abb\n");

        val = rand() % N;
        found = 0;
        timer->start(&timer);
        for (size_t i = 0; i < N; i++)
        {
            if (arr[i] == val)
            {
                timer->stop(&timer);

                printf("%lf ms. ", timer->elapsedTime(&timer));
                found = 1;
                break;
            }
        }
        if (found)
            printf("Encontrado (%i) en abb\n", val);
        else
        {
            timer->stop(&timer);

            printf("%lf ms. ", timer->elapsedTime(&timer));
            printf("No encontrado en abb\n");
        }
    }

    bst->clean(&bst);
    free(arr);
    
    return 0;
}
