#include "Queue.h"

#include <iostream>

void Queue::push(Token &token)
{
    if (front == nullptr)
    {
        front = new Node(token);
        rear = front;
    }
    else
    {
        Node *newNode = new Node(token);
        rear->next = newNode;
        rear = newNode;
    }
}

Token Queue::pop()
{
    Token return_token = front->data;
    Node *new_front = front->next;
    delete front;
    front = new_front;

    return return_token;
}

void Queue::print()
{
    Node *ptr = front;
    while (ptr != nullptr)
    {
        std::cout << ptr->data.string << " ";
        ptr = ptr->next;
    }
}

Queue::Queue() : front(nullptr), rear(nullptr)
{
}

Queue::~Queue()
{
    Node* ptr;
    while (front != nullptr)
    {
        ptr = front;
        front = front->next;

        delete ptr;
    }
}
