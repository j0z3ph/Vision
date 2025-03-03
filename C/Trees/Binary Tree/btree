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
    Node *root;
    void (*insert)(struct BTree **self, size_t value);
    void (*delete)(struct BTree **btree, size_t value);
} BTree;

typedef struct Queue
{
    Node **arr;
    size_t size;
    void (*push)(struct Queue **self, Node *ptr);
    void (*clear)(struct Queue **self);
} Queue;

Queue *newQueue();
void push(Queue **queue, Node *ptr);
void clear(Queue **queue);
Node *newNode(size_t value);
void insert(BTree **btree, size_t value);
BTree *newBTree();
void delete(BTree **btree, size_t value);

void push(Queue **queue, Node *ptr)
{
    if ((*queue)->arr == NULL)
    {
        (*queue)->arr = malloc(sizeof(Node *) * MIN_SIZE);
        (*queue)->arr[(*queue)->size] = ptr;
        (*queue)->size = 1;
    }
    else
    {
        if ((((*queue)->size) % MIN_SIZE) == 0)
        {
            (*queue)->arr = realloc((*queue)->arr, sizeof(Node *) * MIN_SIZE * ((((*queue)->size) / MIN_SIZE) + 1));
        }
        (*queue)->arr[(*queue)->size] = ptr;
        (*queue)->size++;
    }
}

void clear(Queue **queue)
{
    if ((*queue) != NULL)
    {
        if ((*queue)->arr != NULL)
        {
            free((*queue)->arr);
            (*queue)->size = 0;
            (*queue)->arr = NULL;
        }
        free((*queue));
        (*queue) = NULL;
    }
}

Queue *newQueue()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->size = 0;
    queue->arr = NULL;
    queue->push = push;
    queue->clear = clear;
    return queue;
}

Node *newNode(size_t value)
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

void insert(BTree **btree, size_t value)
{
    Queue *queue = newQueue();
    size_t cont = 0;
    if ((*btree)->root == NULL)
    {
        (*btree)->root = newNode(value);
    }
    else
    {
        queue->push(&queue, (*btree)->root);
        while (cont < queue->size)
        {
            if (queue->arr[cont]->left == NULL)
            {
                queue->arr[cont]->left = newNode(value);
                break;
            }
            else
            {
                queue->push(&queue, queue->arr[cont]->left);
            }
            if (queue->arr[cont]->right == NULL)
            {
                queue->arr[cont]->right = newNode(value);
                break;
            }
            else
            {
                queue->push(&queue, queue->arr[cont]->right);
            }
            cont++;
        }
    }
    queue->clear(&queue);
}

void delete(BTree **btree, size_t value)
{
    Queue *queue = newQueue();
    bool inserted = true;
    size_t cont = 0;
    Node *key = NULL;
    if ((*btree)->root != NULL)
    {
        queue->push(&queue, (*btree)->root);
        // builds queue
        while (inserted)
        {
            inserted = false;
            if (queue->arr[cont]->left != NULL)
            {
                queue->push(&queue, queue->arr[cont]->left);
                inserted = true;
            }
            if (queue->arr[cont]->right != NULL)
            {
                queue->push(&queue, queue->arr[cont]->right);
                inserted = true;
            }
            cont++;
        }
        // find value
        for (size_t i = 0; i < queue->size; i++)
        {
            if (queue->arr[i]->value == value)
            {
                key = queue->arr[i];
                break;
            }
        }

        // If found
        if (key != NULL)
        {
            // search for right most node
            cont = -1;
            for (size_t i = 0; i < queue->size; i++)
            {
                if (((i << 1) + 1) >= (queue->size - 1))
                {
                    cont = i;
                    break;
                }
                if (((i << 1) + 2) >= (queue->size - 1))
                {
                    cont = i;
                    break;
                }
            }
            if (cont >= 0)
            {
                if (queue->arr[cont]->right != NULL)
                {
                    key->value = queue->arr[cont]->right->value;
                    free(queue->arr[cont]->right);
                    queue->arr[cont]->right = NULL;
                }
                else
                {
                    key->value = queue->arr[cont]->left->value;
                    free(queue->arr[cont]->left);
                    queue->arr[cont]->left = NULL;
                }
            }
        }
    }
    queue->clear(&queue);
}

void breadthfirstsearch(Node *root)
{
    Queue *queue = newQueue();
    bool inserted = true;
    size_t cont = 0;
    if (root != NULL)
    {
        queue->push(&queue, root);
        while (inserted)
        {
            inserted = false;
            if (queue->arr[cont]->left != NULL)
            {
                queue->push(&queue, queue->arr[cont]->left);
                inserted = true;
            }
            if (queue->arr[cont]->right != NULL)
            {
                queue->push(&queue, queue->arr[cont]->right);
                inserted = true;
            }
            cont++;
        }
        for (size_t i = 0; i < queue->size; i++)
        {
            printf("%i ", queue->arr[i]->value);
        }
    }
    queue->clear(&queue);
}

void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%lu ", root->value);
        inorder(root->right);
    }
}

void preorder(Node *root)
{
    if (root != NULL)
    {
        printf("%lu ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%lu ", root->value);
    }
}

BTree *newBTree()
{
    BTree *btree = malloc(sizeof(BTree));
    btree->root = NULL;
    btree->insert = insert;
    btree->delete = delete;
    return btree;
}

int main()
{
    BTree *tree = newBTree();

    tree->insert(&tree, 5);
    tree->insert(&tree, 3);
    tree->insert(&tree, 1);
    tree->insert(&tree, 2);
    tree->insert(&tree, 8);
    tree->insert(&tree, 10);
    tree->insert(&tree, 11);
    tree->insert(&tree, 7);

    breadthfirstsearch(tree->root);
    printf("\n");
    inorder(tree->root);
    printf("\n");
    preorder(tree->root);
    printf("\n");
    postorder(tree->root);
    printf("\n");

    tree->delete(&tree, 3);
    tree->delete(&tree, 1);
    tree->delete(&tree, 5);
    tree->delete(&tree, 8);

    return 0;
}
