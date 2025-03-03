#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MIN_SIZE 10

typedef struct Node
{
    size_t value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct BTree
{
    Node *arr;
    size_t size;
    size_t __last;
} BTree;

BTree *newBTree()
{
    BTree *tree = malloc(sizeof(BTree));
    tree->arr = NULL;
    tree->size = 0;
    tree->__last = 0;
    return tree;
}

void insert(BTree **tree, size_t value)
{
    if ((*tree)->arr == NULL)
    {
        (*tree)->arr = malloc(sizeof(Node) * MIN_SIZE);
        (*tree)->arr[0].value = value;
        (*tree)->arr[0].left = (*tree)->arr[0].right = NULL;
        (*tree)->size = 1;
    }
    else
    {
        if (((*tree)->size % MIN_SIZE) == 0)
        {
            (*tree)->arr = realloc((*tree)->arr, sizeof(Node) * MIN_SIZE * ((((*tree)->size) / MIN_SIZE) + 1));
        }
        for (size_t i = 0; i < (*tree)->size; i++)
        {
            if ((*tree)->arr[i].left == NULL)
            {
                (*tree)->arr[(i << 1) + 1].value = value;
                (*tree)->arr[(i << 1) + 1].left = (*tree)->arr[(i << 1) + 1].right = NULL;
                (*tree)->arr[i].left = &((*tree)->arr[(i << 1) + 1]);
                (*tree)->size++;
                break;
            }
            else if ((*tree)->arr[i].right == NULL)
            {
                (*tree)->arr[(i << 1) + 2].value = value;
                (*tree)->arr[(i << 1) + 2].left = (*tree)->arr[(i << 1) + 2].right = NULL;
                (*tree)->arr[i].right = &((*tree)->arr[(i << 1) + 2]);
                (*tree)->size++;
                break;
            }
            
        }
    }
}

int main()
{
    BTree *tree = newBTree();
    for (size_t i = 0; i < 1000000; i++)
    {
        insert(&tree, 5);
    }
    
    insert(&tree, 5);
    insert(&tree, 3);
    insert(&tree, 1);
    insert(&tree, 2);
    insert(&tree, 8);
    insert(&tree, 10);
    insert(&tree, 11);
    insert(&tree, 76);
    insert(&tree, 56);
    insert(&tree, 12);
    insert(&tree, 90);
    insert(&tree, 4);
    insert(&tree, 44);
    insert(&tree, 122);


    return 0;
}
