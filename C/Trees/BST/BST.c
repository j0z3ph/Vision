/**
 * @file BST.c
 * @author Jose Luis Cruz (jlcruz@ipn.mx)
 * @brief Source code file with my own Binary Search Tree implementation.
 * Just for educational purposes.
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

Timer *newTimer()
{
    Timer *t = malloc(sizeof(Timer));
    t->_start = 0;
    t->_end = 0;
    t->_elapsed = 0;
    t->elapsedTime = elapsedTime;
    t->start = start;
    t->stop = stop;
    return t;
}
void start(Timer **timer)
{
    (*timer)->_start = clock();
}
void stop(Timer **timer)
{
    (*timer)->_end = clock();
}
double elapsedTime(Timer **timer)
{
    return (double)((*timer)->_end - (*timer)->_start) / (double)(CLOCKS_PER_SEC / 1000);
}

Node *newNode(int value)
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->parent = NULL;
    node->right = NULL;
    return node;
}

BinarySearchTree *newBST()
{
    BinarySearchTree *bst = malloc(sizeof(BinarySearchTree));
    bst->root = NULL;
    bst->clean = clean;
    bst->delete = removeNode;
    bst->insert = insert;
    bst->search = search;
    bst->inorder = inorder;
    bst->posorder = posorder;
    bst->preorder = preorder;
    return bst;
}

void insert(BinarySearchTree **bst, int value)
{
    if ((*bst)->root == NULL)
    {
        (*bst)->root = newNode(value);
    }
    else
    {
        Node *node = (*bst)->root;
        Node *new_node = newNode(value);
        while (1)
        {
            if (value < node->value)
            {
                if (node->left == NULL)
                {
                    node->left = new_node;
                    new_node->parent = node;
                    break;
                }
                else
                {
                    node = node->left;
                }
            }
            else
            {
                if (node->right == NULL)
                {
                    node->right = new_node;
                    new_node->parent = node;
                    break;
                }
                else
                {
                    node = node->right;
                }
            }
        }
    }
}

// Search
Node *search(BinarySearchTree *bst, int value)
{
    if (bst == NULL)
    {
        return NULL;
    }
    else
    {
        Node *node = bst->root;
        while (node != NULL)
        {
            if (node->value == value)
                return node;
            else
            {
                if (value < node->value)
                    node = node->left;
                else
                    node = node->right;
            }
        }
        return NULL;
    }
}

// Delete
void removeNode(BinarySearchTree **bst, int value)
{
    Node *toRemove = search((*bst), value);
    if (toRemove != NULL)
    {
        if (toRemove->left != NULL && toRemove->right != NULL)
        {
            // Case 3

            // MinNode
            Node *min = toRemove->right;
            while (min->left != NULL)
                min = min->left;

            toRemove->value = min->value;

            if (min->parent->left == min)
                min->parent->left = min->right;
            else
                min->parent->right = min->right;
            if (min->right != NULL)
                min->right->parent = min->parent;
            free(min);
        }
        else
        {
            // Case 2
            if (toRemove->parent != NULL)
            {
                if (toRemove->parent->left == toRemove)
                {
                    toRemove->parent->left = toRemove->left != NULL ? toRemove->left : toRemove->right;
                    if (toRemove->parent->left != NULL)
                        toRemove->parent->left->parent = toRemove->parent;
                }
                else
                {
                    toRemove->parent->right = toRemove->left != NULL ? toRemove->left : toRemove->right;
                    if (toRemove->parent->right != NULL)
                        toRemove->parent->right->parent = toRemove->parent;
                }

                free(toRemove);
            }
            else
            {
                // Root
                if (toRemove->left != NULL)
                    (*bst)->root = toRemove->left;
                else
                    (*bst)->root = toRemove->right;
                if ((*bst)->root != NULL)
                    (*bst)->root->parent = NULL;
                free(toRemove);
            }
        }
    }
}

// Delete Tree

void _clean(Node *parent)
{
    if (parent != NULL)
    {
        _clean(parent->left);
        _clean(parent->right);
        free(parent);
    }
}

void clean(BinarySearchTree **bst)
{
    if ((*bst)->root != NULL)
    {
        _clean((*bst)->root);
        (*bst)->root = NULL;
    }
}

// Traverse

void inorder(Node *parent)
{
    if (parent != NULL)
    {
        inorder(parent->left);
        printf("%i ", parent->value);
        inorder(parent->right);
    }
}

void preorder(Node *parent)
{
    if (parent != NULL)
    {
        printf("%i ", parent->value);
        preorder(parent->left);
        preorder(parent->right);
    }
}

void posorder(Node *parent)
{
    if (parent != NULL)
    {
        posorder(parent->left);
        posorder(parent->right);
        printf("%i ", parent->value);
    }
}
