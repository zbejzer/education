#include "Stack.h"

#include <iostream>

void Stack::push(const Token &value)
{
    if (front == nullptr)
    {
        front = new Node(value);
    }
    else
    {
        Node *newNode = new Node(value);
        newNode->next = front;
        front = newNode;
    }
}

Token Stack::pop()
{
    Token return_token = front->token;
    Node *new_front = front->next;
    delete front;
    front = new_front;

    return return_token;
}

const Token &Stack::top() const
{
    return front->token;
}

bool Stack::empty() const
{
    return front == nullptr;
}

void Stack::print()
{
    Node *ptr = front;
    while (ptr != nullptr)
    {
        std::cout << ptr->token << " ";
        ptr = ptr->next;
    }
}

Stack::Stack() : front(nullptr)
{
}

Stack::~Stack()
{
    Node *ptr;
    while (front != nullptr)
    {
        ptr = front;
        front = front->next;

        delete ptr;
    }
}
