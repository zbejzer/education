#pragma once

#include <iostream>

// TODO: Change the is* functions to a single function that returns enum

class Token
{
    static constexpr int TOKEN_SIZE = 20;
    char string[TOKEN_SIZE];

  public:
    Token &operator=(const Token &right);
    Token();
    Token(const char (&string)[TOKEN_SIZE]);

    void addToString(const int num);
    void setString(const char (&string)[TOKEN_SIZE]);
    bool isNumber() const;
    bool isComma() const;
    bool isDot() const;
    bool isLeftParenthesis() const;
    bool isRightParenthesis() const;
    bool isMinMax() const;
    bool isMin() const;
    bool isFunction() const;
    unsigned int getPrecedence() const;
    int toInt() const;
    unsigned int getMinMaxArgCount() const;
    char getFirstChar();

    friend std::ostream &operator<<(std::ostream &os, const Token &token);
    friend std::istream &operator>>(std::istream &is, Token &token);
};

std::ostream &operator<<(std::ostream &os, const Token &token);
std::istream &operator>>(std::istream &is, Token &token);