#include "Node.h"

Node::Node() : next(nullptr)
{
}

Node::Node(Token &token) : next(nullptr)
{
    this->token = token;
}