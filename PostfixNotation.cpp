#include "PostfixNotation.h"

void PostfixNotation::addAndParseToken(const Token &curr_token)
{
    if (curr_token.isNumber())
    {
        output.push(curr_token);
    }
    else if (curr_token.isComma())
    {
        args_counter.top()++;

        while (!operators.top().isLeftParenthesis())
        {
            output.push(operators.top());
            operators.pop();
        }
    }
    else if (curr_token.isLeftParenthesis())
    {
        operators.push(curr_token);
        args_counter.push(1);
    }
    else if (curr_token.isRightParenthesis())
    {
        // assuming the operator stack is not empty, if so, then there are mismatched parentheses
        while (!operators.top().isLeftParenthesis())
        {
            output.push(operators.top());
            operators.pop();
        }
        // assuming the top operator is left parenthesis, so drop it from the stack
        operators.pop();

        if (operators.top().isFunction())
        {
            output.push(operators.top());
            if (operators.top().isMinMax())
            {
                output.back().addToString(args_counter.top());
            }
            operators.pop();
        }
        // again, assume the parentheses are matched, so there has to be at least one arg on the args_counter stack
        args_counter.pop();
    }
    else if (curr_token.isFunction())
    {
        operators.push(curr_token);
    }
    else if (curr_token.isDot())
    {
        while (!operators.empty())
        {
            output.push(operators.top());
            operators.pop();
        }
    }
    else // Operator
    {
        while (!operators.empty() && !operators.top().isLeftParenthesis() &&
               operators.top().getPrecedence() >= curr_token.getPrecedence())
        {
            output.push(operators.top());
            operators.pop();
        }
        operators.push(curr_token);
    }
}

void PostfixNotation::printCurrentStatus() const
{
    std::cout << "Output queue: ";
    output.print();
    std::cout << "\nOperators stack: ";
    operators.print();
    std::cout << "\nParenthesis args stack: ";
    args_counter.print();
    std::cout << "\n";
}

void PostfixNotation::calculate()
{
}

bool PostfixNotation::isCalculated()
{
    return false;
}
