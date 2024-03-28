#include <iostream>

#include "Constants.h"
#include "PostfixNotation.h"

using namespace std;

int main()
{
    size_t case_count;
    char string[TOKEN_SIZE] = "";
    Token token;
    cin >> case_count;

    for (size_t i = 0; i < case_count; i++)
    {
        PostfixNotation postfix_notation;
        do
        {
            cin >> string;
            token.setString(string);
            postfix_notation.addAndParseToken(token);
        } while (string[0] != '.');

        postfix_notation.printCurrentStatus();

        // while (!postfix_notation.isCalculated())
        //{
        //       postfix_notation.printCurrentStatus();
        //     // postfix_notation.calculateNextStep();
        // }
    }

    return 0;
}