#pragma once

#include "Constants.h"

struct Token
{
    char string[TOKEN_SIZE];

    Token &operator=(const Token &right);
    Token();
    Token(const char (&string)[TOKEN_SIZE]);

    void setString(const char (&string)[TOKEN_SIZE]);
    bool isNumber() const;
    bool isComma() const;
    bool isDot() const;
    bool isLeftParenthesis() const;
    bool isRightParenthesis() const;
    bool isMinMax() const;
};