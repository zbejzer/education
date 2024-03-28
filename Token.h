#pragma once

#include "Constants.h"

struct Token
{
    char string[TOKEN_SIZE];

    Token &operator=(const Token &right);
    Token();
    Token(const char (&string)[TOKEN_SIZE]);

    bool isNumber() const;
};