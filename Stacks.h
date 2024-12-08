#ifndef STACKS_H
#define STACKS_H
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class Stacks {
    public:
        Node* topNode;
        Stacks(): topNode(nullptr) {}
        void push(int value) {
            Node* newNode = new Node();
            newNode -> data = value;
            newNode -> next = topNode;
            topNode = newNode;
        }

        void pop() {
            if(isEmpty()) {
                return;
            }
            Node* temp = topNode;
            topNode = topNode -> next;
            delete temp;
        }

        int top() {
            if(isEmpty()) {
                return -1;
            }
            return topNode -> data;
        }

        bool isEmpty() {
            return topNode == nullptr;
        }
};

#endif