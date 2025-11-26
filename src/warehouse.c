#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command_parser.h"
#include "product.h"

int product_count;
Product *products;
bool pdf_mode;

int main(int argc, char *argv[])
{
    int ch_buffer = 0;
    size_t line_length = 1;
    char *line_buffer = malloc(sizeof(char));
    line_buffer[0] = '\0';

    pdf_mode = (strcmp(argv[1], "pdf") == 0);

    while ((ch_buffer = getchar()) != EOF)
    {
        if (ch_buffer == '\n')
        {
            ParseCommand(line_buffer);
            line_buffer = realloc(line_buffer, sizeof(char));
            line_buffer[0] = '\0';
        }
        else
        {
            line_length++;
            line_buffer = realloc(line_buffer, line_length * sizeof(char));
            line_buffer[line_length - 2] = (char)ch_buffer;
            line_buffer[line_length - 1] = '\0';
        }
    }

    ParseCommand(line_buffer);
    free(line_buffer);
    free(products);

    return 0;
}