#include "Token.h"

#include <algorithm>

Token &Token::operator=(const Token &other)
{
    std::copy(std::begin(other.string), std::end(other.string), std::begin(this->string));

    return *this;
}

Token::Token()
{
    strcpy(string, "");
}

Token::Token(const char (&string)[TOKEN_SIZE])
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
