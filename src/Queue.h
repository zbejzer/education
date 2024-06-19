#pragma once

#include "Node.h"
#include "Token.h"

template <typename T> class Queue
{
    Node<T> *front_node, *rear_node;

  public:
    void push(const T &val);
    void pop();
    const T &back() const;
    T &back();
    const T &front() const;
    T &front();
    bool empty() const;
    void print() const;
    void print(unsigned int whitespace_count) const;

    Queue();
    ~Queue();
};

template <typename T> void Queue<T>::push(const T &val)
{
    if (front_node == nullptr)
    {
        rear_node = new Node<T>(val);
        front_node = rear_node;
    }
    else
    {
        Node<T> *newNode = new Node<T>(val);
        rear_node->next = newNode;
        rear_node = newNode;
    }
}

template <typename T> void Queue<T>::pop()
{
    Node<T> *new_front = front_node->next;
    delete front_node;
    front_node = new_front;

    if (front_node == nullptr)
    {
        rear_node = nullptr;
    }
}

template <typename T> const T &Queue<T>::back() const
{
    return rear_node->value;
}

template <typename T> T &Queue<T>::back()
{
    return rear_node->value;
}

template <typename T> const T &Queue<T>::front() const
{
    return front_node->value;
}

template <typename T> T &Queue<T>::front()
{
    return front_node->value;
}

template <typename T> bool Queue<T>::empty() const
{
    return front_node == nullptr;
}

template <typename T> void Queue<T>::print() const
{
    Node<Token> *ptr = front_node;
    while (ptr != nullptr)
    {
        std::cout << ptr->value << " ";
        ptr = ptr->next;
    }
}

template <typename T> inline void Queue<T>::print(unsigned int whitespace_count) const
{
    Node<Token> *ptr = front_node;
    while (ptr != nullptr)
    {
        std::cout << ptr->value;
        for (unsigned int i = 0; i < whitespace_count; i++)
        {
            std::cout << " ";
        }
        ptr = ptr->next;
    }
}

template <typename T> Queue<T>::Queue() : front_node(nullptr), rear_node(nullptr)
{
}

template <typename T> Queue<T>::~Queue()
{
    while (!this->empty())
    {
        this->pop();
    }
}
