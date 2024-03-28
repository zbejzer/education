#pragma once

#include "Node.h"

class Stack
{
    Node *front;

  public:
    void push(Token &token);
    Token pop();
    void print();

    Stack();
    ~Stack();
};
