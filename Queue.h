#pragma once

#include "Node.h"

class Queue
{
    Node *front, *rear;

  public:
    void push(Token &token);
    Token pop();
    void print();

    Queue();
    ~Queue();
};
