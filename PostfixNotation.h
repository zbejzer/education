#pragma once

#include "Constants.h"
#include "Stack.h"
#include "Queue.h"

class PostfixNotation
{
    Queue output;
    Stack operators;

  public:
    void addAndParseToken(Token token);
    void printCurrentStatus();
    void calculate();

    bool isCalculated();
};
