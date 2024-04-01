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

    void calculateNextStep();

  public:
    void addAndParseToken(const Token &token);
    void printCurrentStatus() const;
    void printOutputQueue() const;
    void printCalculationOperandsStack() const;
    void calculate();

    bool isCalculated();
};
