#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <iostream>
using namespace std;

struct AVL_Node {
    int data;
    AVL_Node* left;
    AVL_Node* right;
    int height;

    AVL_Node(int value);
};

class AVLTree {
public:
    AVL_Node* root;

    AVLTree();

    int height(AVL_Node* node);
    int getBalance(AVL_Node* node);
    AVL_Node* rightRotate(AVL_Node* y);
    AVL_Node* leftRotate(AVL_Node* x);
    AVL_Node* insert(AVL_Node* node, int value);
    AVL_Node* search(AVL_Node* node, int value);
    void inorder(AVL_Node* node);
};

#endif
