#pragma once

#include "Token.h"

struct Node
{
    Node *next;
    Token data;

    Node();
    Node(Token &value);
};
