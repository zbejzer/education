#include <iostream>

#include "PostfixNotation.h"

using namespace std;

int main()
{
    size_t case_count;
    Token token;
    cin >> case_count;

    for (size_t i = 0; i < case_count; i++)
    {
        PostfixNotation postfix_notation;
        do
        {
            cin >> token;
            postfix_notation.addAndParseToken(token);
        } while (!token.isDot());

        // DEBUG
        // postfix_notation.printCurrentStatus();
        postfix_notation.printOutputQueue();
        postfix_notation.calculate();
        postfix_notation.printCalculationOperandsStack();
    }

    return 0;
}