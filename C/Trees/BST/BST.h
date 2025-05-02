/**
 * @file BST.h
 * @author Jose Luis Cruz (jlcruz@ipn.mx)
 * @brief Header file with my own Binary Search Tree implementation.
 * Just for educational purposes.
 * @version 0.1
 * @date 2025-05-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef __BST_H__
#define __BST_H__

typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

typedef struct BinarySearchTree
{
    Node *root;
    void (*insert)(struct BinarySearchTree **self, int value);
    struct Node *(*search)(struct BinarySearchTree *self, int value);
    void (*delete)(struct BinarySearchTree **self, int value);
    void (*clean)(struct BinarySearchTree **self);
    void (*inorder)(struct Node *parent);
    void (*preorder)(struct Node *parent);
    void (*posorder)(struct Node *parent);
} BinarySearchTree;

typedef struct Timer
{
    unsigned long _start, _end;
    double _elapsed;
    /// @brief Start the timer
    /// @param self Pointer to the timer instance
    void (*start)(struct Timer **self);
    /// @brief Stop the timer
    /// @param self Pointer to the timer instance
    void (*stop)(struct Timer **self);
    /// @brief Gets the elapsed time mesured by the timer
    /// @param self Pointer to the timer instance
    /// @return Double value representing the elapsed time in milliseconds
    double (*elapsedTime)(struct Timer **self);
} Timer;

Node *newNode(int value);
BinarySearchTree *newBST();
void insert(BinarySearchTree **bst, int value);
Node *search(BinarySearchTree *bst, int value);
void removeNode(BinarySearchTree **bst, int value);
void clean(BinarySearchTree **bst);
void inorder(Node *parent);
void preorder(Node *parent);
void posorder(Node *parent);

/// @brief Creates a new instance of timer
/// @return Pointer to the timer instance
Timer *newTimer();

void start(Timer **timer);

void stop(Timer **timer);

double elapsedTime(Timer **timer);

#endif