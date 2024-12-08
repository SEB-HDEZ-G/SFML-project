#ifndef QUEUE_H
#define QUEUE_H

class Queue {
public:
    int front;
    int rear;
    int size;
    int* queue;
    int capacity;

    Queue(int capacity);
    bool isEmpty();
    bool isFull();
    void enqueue(int value);
    void dequeue();
    int peek();
    ~Queue();
};

#endif
