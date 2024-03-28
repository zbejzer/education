#include "Stack.h"

#include <iostream>

void Stack::push(Token &token)
{
    if (front == nullptr)
    {
        front = new Node(token);
    }
    else
    {
        Node *newNode = new Node(token);
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
