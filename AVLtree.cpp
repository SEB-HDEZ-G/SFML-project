#include "AVLtree.h"

// AVL_Node constructor
AVL_Node::AVL_Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}

// AVLTree constructor
AVLTree::AVLTree() : root(nullptr) {}

// Height of a node
int AVLTree::height(AVL_Node* node) {
    return node ? node->height : 0;
}

// Balance factor of a node
int AVLTree::getBalance(AVL_Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Right rotation
AVL_Node* AVLTree::rightRotate(AVL_Node* y) {
    AVL_Node* x = y->left;
    AVL_Node* z = x->right;

    x->right = y;
    y->left = z;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

// Left rotation
AVL_Node* AVLTree::leftRotate(AVL_Node* x) {
    AVL_Node* y = x->right;
    AVL_Node* z = y->left;

    y->left = x;
    x->right = z;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// Insert a value into the AVL tree
AVL_Node* AVLTree::insert(AVL_Node* node, int value) {
    if (!node) return new AVL_Node(value);

    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    } else {
        return node; // Duplicate keys are not allowed
    }

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Balance the node
    int balance = getBalance(node);

    // Left-left case
    if (balance > 1 && value < node->left->data) {
        return rightRotate(node);
    }

    // Right-right case
    if (balance < -1 && value > node->right->data) {
        return leftRotate(node);
    }

    // Left-right case
    if (balance > 1 && value > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right-left case
    if (balance < -1 && value < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Search for a value in the AVL tree
AVL_Node* AVLTree::search(AVL_Node* node, int value) {
    if (!node || node->data == value) {
        return node;
    }

    if (value < node->data) {
        return search(node->left, value);
    }

    return search(node->right, value);
}

// Inorder traversal (processes nodes in sorted order)
void AVLTree::inorder(AVL_Node* root) {
    if (!root) return;

    inorder(root->left);
    cout << root->data << " "; // Example processing (print node value)
    inorder(root->right);
}
