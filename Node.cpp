#include "Node.h"

Node::Node() : prev(nullptr), next(nullptr)
{
}

Node::Node(Token &token) : prev(nullptr), next(nullptr)
{
    this->data = token;
}