#include <iostream>

#include "PostfixNotation.h"

using namespace std;

// TODO: Adjust cout output to match the desired one
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

        postfix_notation.printCurrentStatus();

        while (!postfix_notation.isCalculated())
        {
            cout << "Calculating next step\n";
            postfix_notation.calculateNextStep();
            postfix_notation.printCurrentStatus();
        }
    }

    return 0;
}