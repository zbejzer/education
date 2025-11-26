#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command_parser.h"
#include "config.h"
#include "product.h"

size_t kProductCount;
Product *kProducts;
bool kPdfMode;
const char kSaveFileName[] = "store.txt";

int main(int argc, char *argv[])
{
    char command_buffer[COMMAND_SIZE_MAX] = "";
    char args_buffer[ARGS_SIZE_MAX] = "";

    if (argc > 1)
    {
        kPdfMode = (strcmp(argv[1], "pdf") == 0);
    }

    while (scanf("%" XSTR(COMMAND_SIZE_MAX) "s %" XSTR(ARGS_SIZE_MAX) "[^\n]", command_buffer, args_buffer) != EOF)
    {
        HandleCommand(command_buffer, args_buffer);
    }

    free(kProducts);

    return 0;
}