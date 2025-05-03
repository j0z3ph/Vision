/**
 * @file HT.h
 * @author Jose Luis Cruz (jlcruz@ipn.mx)
 * @brief HashTable implementation
 * @version 0.1
 * @date 2025-05-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __HT_H__
#define __HT_H__
#include <stdio.h>

typedef struct Node
{
    size_t key;
    double data;
} Node;

typedef struct List
{
    Node *list;
    size_t _size;
    void (*add2list)(struct List **self, size_t key, double value);
    Node *(*searchOnList)(struct List **self, size_t key);
} List;

typedef struct HashTable
{
    List **table;
    size_t _size;
    void (*addData)(struct HashTable **self, size_t key, double value);
    Node *(*searchData)(struct HashTable **self, size_t key);
    void (*printHashTable)(struct HashTable **self);
    void (*clear)(struct HashTable **self);
} HashTable;

void add2list(List **list, size_t key, double value);

Node *searchOnList(List **list, size_t key);

void addData(HashTable **ht, size_t key, double value);

Node *searchData(HashTable **ht, size_t key);

void printHashTable(HashTable **ht);

void clear(HashTable **ht);

List *newList();

Node *newNode(size_t key, double value);

HashTable *newHashTable(size_t size);

#endif