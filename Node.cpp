#include "Node.h"

Node::Node() : next(nullptr)
{
}

Node::Node(const Token &token) : next(nullptr)
{
    this->token = token;
}