#include "Queue.h"
#include <iostream>
using namespace std;

Queue::Queue(int capacity) {
    front = -1;
    rear = -1;
    size = capacity;
    queue = new int[size];
}

bool Queue::isEmpty() {
    return front == -1;
}

bool Queue::isFull() {
    return rear == size-1;
}

void Queue::enqueue(int value) {
    if(isFull()) {
        return;
    }
    if(front == -1) {
        front = 0;
    }
    queue[++rear] = value;
};


void Queue::dequeue() {
    if (isEmpty()) {
        return;
    }
    front++;  //increment front to delete the element

    if (front > rear) {
        front = rear = -1;
    }
}

int Queue::peek() {
    if (isEmpty()) {
        return -1;
    }
    return queue[front];  //return front element
}

//Destructor: clear the memory assigned for the array
Queue::~Queue() {
    delete[] queue;
}