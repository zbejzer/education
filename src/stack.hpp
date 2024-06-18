#pragma once

#include <iostream>

#include "node.hpp"

template <typename T> class Stack
{
    Node<T> *front_node;

  public:
    void push(const T &val);
    void pop();
    const T &top() const;
    T &top();
    bool empty() const;
    void print() const;

    Stack();
    ~Stack();
};

template <typename T> void Stack<T>::push(const T &val)
{
    if (front_node == nullptr)
    {
        front_node = new Node<T>(val);
    }
    else
    {
        Node<T> *newNode = new Node<T>(val);
        newNode->next = front_node;
        front_node = newNode;
    }
}

template <typename T> void Stack<T>::pop()
{
    Node<T> *new_front = front_node->next;
    delete front_node;
    front_node = new_front;
}

template <typename T> const T &Stack<T>::top() const
{
    return front_node->value;
}

template <typename T> T &Stack<T>::top()
{
    return front_node->value;
}

template <typename T> bool Stack<T>::empty() const
{
    return front_node == nullptr;
}

template <typename T> void Stack<T>::print() const
{
    Node<T> *ptr = front_node;
    while (ptr != nullptr)
    {
        std::cout << ptr->value << " ";
        ptr = ptr->next;
    }
    std::cout << "\n";
}

template <typename T> Stack<T>::Stack() : front_node(nullptr)
{
}

template <typename T> Stack<T>::~Stack()
{
    while (!this->empty())
    {
        this->pop();
    }
}