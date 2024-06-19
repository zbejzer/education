#include "Token.h"

#include <cstring>

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

// the only thing that we add to is MIN and MAX, so we can assume
// the starting point is always 3 chars past the beginning of the string
// there is also an assumption that the num has no more than 16 digits
void Token::addToString(const int num)
{
    sprintf(this->string + 3 * sizeof(char), "%d", num);
}

void Token::setString(const char (&string)[TOKEN_SIZE])
{
    std::strcpy(this->string, string);
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
    return string[0] == 'M';
}

// assert the token is a MIN or MAX
bool Token::isMin() const
{
    return string[1] == 'I';
}

bool Token::isFunction() const
{
    return string[0] == 'M' || string[0] == 'N' || string[0] == 'I';
}

unsigned int Token::getPrecedence() const
{
    switch (string[0])
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case 'I':
        return 3;
    case 'N':
        return 4;
    case 'M':
        return 5;
    default:
        return 0;
    }
}

// assert the token is an int
int Token::toInt() const
{
    return atoi(string);
}

// assert the token is a MIN or MAX
unsigned int Token::getMinMaxArgCount() const
{
    return atoi(string + 3 * sizeof(char));
}

char Token::getFirstChar()
{
    return string[0];
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