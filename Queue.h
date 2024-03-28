#pragma once

#include "Node.h"

class Queue
{
    Node *front, *rear;

  public:
    void enqueue(Token &token);
    Token dequeue();
    void print();

    Queue();
    ~Queue();
};
