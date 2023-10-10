#include <iostream>
#include <malloc.h>

using namespace std;

int main()
{
    unsigned int mode = 0, rows = 0, columns = 0, counter = 0;
    char letter_a, letter_b;
    cin >> mode >> letter_a;
    if (mode == 1)
    {
        cin >> letter_b;
    }
    cin >> rows >> columns;

    char *array = (char *)malloc(rows * columns * sizeof(char));

    for (size_t n = 0; n < rows; n++)
    {
        for (size_t m = 0; m < columns; m++)
        {
            cin >> array[n * columns + m];
        }
    }

    for (size_t n = 0; n < rows; n++)
    {
        for (size_t m = 0; m < columns; m++)
        {
            if (array[n * columns + m] == letter_a)
            {
                if (mode == 0)
                {
                    counter++;
                } else
                {
                    array[n * columns + m] = letter_b;
                }
            }
        }
    }

    if (mode == 0)
    {
        cout << counter;
    } else
    {
        for (size_t n = 0; n < rows; n++)
        {
            for (size_t m = 0; m < columns; m++)
            {
                cout << array[n * columns + m] << " ";
            }
            cout << endl;
        }
    }

    free(array);

    return 0;
}