#include "Token.h"

#include <algorithm>
#include <cstring>
#include <iostream>

Token &Token::operator=(const Token &other)
{
    this->setString(other.string);

    return *this;
}

Token::Token()
{
    string[0] = '\0';
}

Token::Token(const char (&string)[TOKEN_SIZE])
{
    this->setString(string);
}

void Token::setString(const char (&string)[TOKEN_SIZE])
{
    std::copy(std::begin(string), std::end(string), std::begin(this->string));
}

bool Token::isNumber() const
{
    return string[0] >= '0' && string[0] <= '9';
}

bool Token::isComma() const
{
    return string[0] == ',';
}

bool Token::isDot() const
{
    return string[0] == '.';
}

bool Token::isLeftParenthesis() const
{
    return string[0] == '(';
}

bool Token::isRightParenthesis() const
{
    return string[0] == ')';
}

bool Token::isMinMax() const
{
    return strcmp(string, "MAX") == 0 || strcmp(string, "MIN") == 0;
}

std::ostream &operator<<(std::ostream &os, const Token &token)
{
    os << token.string;

    return os;
}

std::istream &operator>>(std::istream &is, Token &token)
{
    is >> token.string;
    return is;
}
