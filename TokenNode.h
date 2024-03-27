#pragma once

#include "Constants.h"

struct Token
{
    char data[TOKEN_SIZE];

    Token &operator=(const Token &right);
    Token();
    Token(char string[TOKEN_SIZE]);

    bool isNumber();
};

struct Node
{
    Node *prev, *next;
    Token data;

    Node();
    Node(Token &value);
};
