/**
 * @file HT.c
 * @author Jose Luis Cruz (jlcruz@ipn.mx)
 * @brief HashTable implementation
 * @version 0.1
 * @date 2025-05-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HT.h"

#define HASH_FN(k,s) (k&(s-1))

void add2list(List **list, size_t key, double value)
{
    if ((*list)->list == NULL)
    {
        (*list)->list = malloc(sizeof(Data));
        (*list)->list[0].key = key;
        (*list)->list[0].data = value;
        (*list)->_size = 1;
    }
    else
    {
        (*list)->list = realloc((*list)->list, sizeof(Data) * ((*list)->_size + 1));
        (*list)->list[(*list)->_size].key = key;
        (*list)->list[(*list)->_size].data = value;
        (*list)->_size++;
    }
}

Data *searchOnList(List **list, size_t key)
{
    if ((*list)->list != NULL)
    {
        for (size_t i = 0; i < (*list)->_size; i++)
        {
            if ((*list)->list[i].key == key)
                return &((*list)->list[i]);
        }
    }
    return NULL;
}

void addData(HashTable **ht, size_t key, double value)
{
    //size_t index = key % (*ht)->_size;
    size_t index = HASH_FN(key,(*ht)->_size);
    (*ht)->table[index]->add2list(&((*ht)->table[index]), key, value);
}

Data *searchData(HashTable **ht, size_t key)
{
    //size_t index = key % (*ht)->_size;
    size_t index = HASH_FN(key,(*ht)->_size);
    return (*ht)->table[index]->searchOnList(&((*ht)->table[index]), key);
}

void printHashTable(HashTable **ht)
{
    if ((*ht)->table != NULL)
    {
        for (size_t i = 0; i < (*ht)->_size; i++)
        {
            printf("[%li] ", i);
            for (size_t j = 0; j < (*ht)->table[i]->_size; j++)
            {
                printf("(%li,%lf)  ", (*ht)->table[i]->list[j].key, (*ht)->table[i]->list[j].data);
            }
            printf("\n");
        }
    }
}

void clear(HashTable **ht)
{
    if ((*ht)->table != NULL)
    {
        for (size_t i = 0; i < (*ht)->_size; i++)
        {
            if ((*ht)->table[i]->list != NULL)
                free((*ht)->table[i]->list);
        }
        free((*ht)->table);
        (*ht)->table = NULL;
    }
}

List *newList()
{
    List *l = malloc(sizeof(List));
    l->list = NULL;
    l->_size = 0;
    l->add2list = add2list;
    l->searchOnList = searchOnList;
    return l;
}

Data *newData(size_t key, double value)
{
    Data *node = malloc(sizeof(Data));
    node->data = 0.0;
    node->key = 0;
    return node;
}

HashTable *newHashTable(size_t size)
{
    HashTable *ht = malloc(sizeof(HashTable));

    // Computing the size (should be power of 2)
    size_t _size = log2(size);

    if (pow(2, _size) == size)
        _size = size;
    else
        _size = pow(2, _size + 1);

    ht->table = malloc(sizeof(List *) * _size);
    ht->_size = _size;
    for (size_t i = 0; i < _size; i++)
    {
        ht->table[i] = newList();
    }

    ht->addData = addData;
    ht->searchData = searchData;
    ht->printHashTable = printHashTable;
    ht->clear = clear;
    return ht;
}
