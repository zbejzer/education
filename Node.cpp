#include "Node.h"

Node::Node() : next(nullptr)
{
}

Node::Node(Token &token) : next(nullptr)
{
    this->data = token;
}