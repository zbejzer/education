#pragma once

#include "Token.h"
#include "Stack.h"
#include "Queue.h"

class PostfixNotation
{
    Queue<Token> output;
    Stack<Token> operators;
    Stack<int> args_counter;
    Stack<int> calc_operands;

  public:
    void addAndParseToken(const Token &token);
    void printCurrentStatus() const;
    void calculateNextStep();

    bool isCalculated();
};
