#pragma once

#include "Node.h"

class Stack
{
    Node *front;

  public:
    void push(const Token &token);
    Token pop();
    const Token &top() const;
    bool empty() const;
    void print();

    Stack();
    ~Stack();
};
