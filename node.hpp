#pragma once

template <typename T> struct Node
{
    Node *next;
    T value;

    Node();
    Node(const T &value);
};

template <typename T> Node<T>::Node() : next(nullptr)
{
}

template <typename T> Node<T>::Node(const T &value) : value(value), next(nullptr)
{
}