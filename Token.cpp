#include "Token.h"

#include <algorithm>
#include <cstring>

Token &Token::operator=(const Token &other)
{
    std::copy(std::begin(other.string), std::end(other.string), std::begin(this->string));

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
    if (string[0] >= '0' && string[0] <= '9')
    {
        return true;
    }

    return false;
}

bool Token::isComma() const
{
    if (string[0]== ',')
    {
        return true;
    }

    return false;
}

bool Token::isDot() const
{
    if (string[0] == '.')
    {
        return true;
    }

    return false;
}

bool Token::isLeftParenthesis() const
{
    if (string[0] == '(')
    {
        return true;
    }

    return false;
}

bool Token::isRightParenthesis() const
{
    if (string[0] == ')')
    {
        return true;
    }

    return false;
}

bool Token::isMinMax() const
{
    if (strcmp(string, "MAX") == 0 || strcmp(string, "MIN") == 0)
    {
        return true;
    }

    return false;
}
