#pragma once

#include "Token.h"

struct Node
{
    Node *next;
    Token token;

    Node();
    Node(const Token &value);
};
