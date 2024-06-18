#include <cstdio>
#include <cstring>

#include "board.hpp"
#include "handle_question.hpp"
#include "pawns.hpp"

constexpr int question_buff_size = 96;

//
// Transforming this input
//
//           ---
//        --<   >--
//     --< b >-<   >--
//  --< r >-<   >-<   >--
// < b >-< b >-<   >-< r >
//  --<   >-< r >-< b >--
//     --<   >-< r >--
//        --<   >--
//           ---
//
// into array like that
//
// /-------\
// | | | |r|
// |-+-+-+-|
// |b| | |b|
// |-+-+-+-|
// |r|b|r|r|
// |-+-+-+-|
// |b| | | |
// \-------/
//

int main()
{
    char buff[question_buff_size] = "";
    fgets(buff, question_buff_size, stdin);

    while (!feof(stdin) && !ferror(stdin))
    {
        Board board;
        board.size = static_cast<unsigned char>((strlen(buff) - 2) / 3);
        buff[0] = '\0';

        for (unsigned char line = 0; line < board.size * 2; line++)
        {
            unsigned char offset = 0;
            while (buff[0] != '\n')
            {
                buff[0] = fgetc(stdin);

                if (buff[0] == '<')
                {
                    unsigned char row, col;
                    static_cast<void>(fgetc(stdin));
                    buff[0] = fgetc(stdin);

                    if (line < board.size)
                    {
                        row = line - offset;
                        col = offset;
                    }
                    else
                    {
                        row = board.size - offset - 1;
                        col = line - board.size + offset + 1;
                    }

                    if (buff[0] == 'r')
                    {
                        board.addPawn(PawnColour::Red, col, row);
                    }
                    else if (buff[0] == 'b')
                    {
                        board.addPawn(PawnColour::Blue, col, row);
                    }
                    else
                    {
                        board.addPawn(PawnColour::Empty, col, row);
                    }
                    offset++;
                }
            }
            buff[0] = '\0';
        }

        board.updateBlueBoard();
        // board.debugPrint();

        buff[0] = '\0';
        while (fgets(buff, question_buff_size, stdin) != nullptr && buff[0] != ' ' && !feof(stdin) && !ferror(stdin))
        {
            buff[strlen(buff) - 1] = '\0'; // Remove included \n character
            handleQuestion(buff, board);
        }
        fputc('\n', stdout);
    }

    return 0;
}