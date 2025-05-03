/**
 * @file main.c
 * @author Jose Luis Cruz (jlcruz@ipn.mx)
 * @brief 
 * @version 0.1
 * @date 2025-05-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"HT.h"

 #define TABLE_SIZE 100000
 #define N 100000000


int main()
{
    srand(time(NULL));
    HashTable *ht = newHashTable(TABLE_SIZE);
    size_t *keys, idx, aux2;
    keys = malloc(sizeof(size_t) * N);

    // generamos las llaves
    for (size_t i = 0; i < N; i++)
    {
        keys[i] = i+1;    
    }

    // mezclamos
    for (size_t i = 0; i < N; i++)
    {
        idx = rand()%N;
        aux2 = keys[idx];
        keys[idx] = keys[i];
        keys[i] = aux2;
    }

    // agregamos a la hashtable

    for (size_t i = 0; i < N; i++)
    {
        ht->addData(&ht, keys[i], (double)rand()/(double)N);
    }


    // Imprimimos
    // ht->printHashTable(&ht);
    
    // Buscamos
    for (size_t i = 0; i < 50; i++)
    {
        aux2 = rand()%(N*2);
        if(ht->searchData(&ht, aux2) != NULL)
        printf("Encontrado (%lu)\n", aux2);
        else 
        printf("NO Encontrado (%lu)\n", aux2);
    }
    
    ht->clear(&ht);
    free(keys);

    return 0;
}
