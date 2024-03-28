#pragma once

#include "Constants.h"

#include <iostream>

class Token
{
    char string[TOKEN_SIZE];

  public:
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

    friend std::ostream &operator<<(std::ostream &os, const Token &token);
};