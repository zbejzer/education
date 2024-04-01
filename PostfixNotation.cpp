#include "PostfixNotation.h"

#include <algorithm>

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
    std::cout << "\Calculator operands stack: ";
    calc_operands.print();
    std::cout << "\n";
}

// TODO: Handle division by 0 error
void PostfixNotation::calculateNextStep()
{
    while (output.front().isNumber())
    {
        calc_operands.push(output.front().toInt());
        output.pop();
    }
    if (!output.empty())
    {
        // now the top of output is a function

        int result;

        switch (output.front().getFirstChar())
        {
        case 'N': {
            result = -calc_operands.top();
            calc_operands.pop();
            break;
        }
        case '+': {
            int arg2 = calc_operands.top();
            calc_operands.pop();
            int arg1 = calc_operands.top();
            calc_operands.pop();
            result = arg1 + arg2;
            break;
        }
        case '-': {
            int arg2 = calc_operands.top();
            calc_operands.pop();
            int arg1 = calc_operands.top();
            calc_operands.pop();
            result = arg1 - arg2;
            break;
        }
        case '*': {
            int arg2 = calc_operands.top();
            calc_operands.pop();
            int arg1 = calc_operands.top();
            calc_operands.pop();
            result = arg1 * arg2;
            break;
        }
        case '/': {
            int arg2 = calc_operands.top();
            calc_operands.pop();
            int arg1 = calc_operands.top();
            calc_operands.pop();
            result = arg1 / arg2;
            break;
        }
        // IF
        case 'I': {
            int arg3 = calc_operands.top();
            calc_operands.pop();
            int arg2 = calc_operands.top();
            calc_operands.pop();
            int arg1 = calc_operands.top();
            calc_operands.pop();
            if (arg1 > 0)
            {
                result = arg2;
            }
            else
            {
                result = arg3;
            }
            break;
        }
        // assuming the only functions starting with M are MIN and MAX
        case 'M': {
            unsigned int arg_count = output.front().getMinMaxArgCount() - 1;
            result = calc_operands.top();
            calc_operands.pop();
            int arg1;
            if (output.front().isMin())
            {
                for (int i = 0; i < arg_count; i++)
                {
                    arg1 = calc_operands.top();
                    calc_operands.pop();
                    result = std::min(result, arg1);
                }
            }
            else
            {
                for (int i = 0; i < arg_count; i++)
                {
                    arg1 = calc_operands.top();
                    calc_operands.pop();
                    result = std::max(result, arg1);
                }
            }
            break;
        }
        default:
            break;
        }

        calc_operands.push(result);
        output.pop();
    }
}

bool PostfixNotation::isCalculated()
{
    return output.empty();
}
