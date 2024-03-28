#include "PostfixNotation.h"

#include "Helpers.h"

void PostfixNotation::addAndParseToken(Token token)
{
    if (token.isNumber())
    {
        output.push(token);
    }
}

void PostfixNotation::printCurrentStatus()
{
    output.print();
}

void PostfixNotation::calculate()
{
}

bool PostfixNotation::isCalculated()
{
    return false;
}
