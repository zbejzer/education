#pragma once

#include "Node.h"

class Queue
{
    Node *front, *rear;

  public:
    void push(const Token &token);
    Token pop();
    void print();

    Queue();
    ~Queue();
};
