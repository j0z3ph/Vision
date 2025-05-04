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
#include <math.h>
#include "BST.h"
#include "HT.h"

#define TABLE pow(2,17)
//#define TABLE 8
#define N 100000000
//#define N 50

int main()
{
    BinarySearchTree *bst = newBST();
    HashTable *ht = newHashTable(TABLE);
    Timer *timer = newTimer();
    size_t aux;
    int *arr = NULL, cont = 0, val, found;
    Node *res;
    Data *resHT;

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

    timer->start(&timer);

    for (size_t i = 0; i < N; i++)
    {
        aux = rand() % N;
        ht->addData(&ht, aux, aux);
    }

    timer->stop(&timer);

    printf("%lf ms\n", timer->elapsedTime(&timer));

    //ht->printHashTable(&ht);

    //return 0;

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
            printf("Encontrado (%i) en arreglo\n", val);
        else
        {
            timer->stop(&timer);

            printf("%lf ms. ", timer->elapsedTime(&timer));
            printf("No encontrado en arreglo\n");
        }

        timer->start(&timer);
        resHT = ht->searchData(&ht, rand()%N);
        timer->stop(&timer);

        printf("%lf ms. ", timer->elapsedTime(&timer));

        if (resHT != NULL)
            printf("Encontrado (%.0lf) en ht\n", resHT->data);
        else
            printf("No encontrado en ht\n");
    }

    bst->clean(&bst);
    free(arr);
    
    return 0;
}
