#pragma once

#include "Token.h"

struct Node
{
    Node *prev, *next;
    Token data;

    Node();
    Node(Token &value);
};
