#include "TokenNode.h"

#include <algorithm>

Node::Node() : prev(nullptr), next(nullptr)
{
}

Node::Node(Token &token) : prev(nullptr), next(nullptr)
{
    this->data = token;
}

Token &Token::operator=(const Token &other)
{
    std::copy(std::begin(other.data), std::end(other.data), std::begin(this->data));

    return *this;
}

Token::Token()
{
    strcpy(data, "");
}

Token::Token(char string[TOKEN_SIZE])
{
    strcpy(data, string);
}

bool Token::isNumber()
{
    if (data[0] >= '0' && data[0] <= '9')
    {
        return true;
    }

    return false;
}
