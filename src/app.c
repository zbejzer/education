#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "controller.h"
#include "product.h"
#include "render.h"

int main(int argc, char *argv[])
{
    char line_buffer[LINE_SIZE_MAX] = "";
    char command[COMMAND_SIZE_MAX] = "";
    char args[FILENAME_MAX] = "";

    if (argc > 1)
    {
        kPdfMode = (strcmp(argv[1], "pdf") == 0);
    }

    while (scanf("%" XSTR(LINE_SIZE_MAX) "[^\n]", line_buffer) != EOF)
    {
        ParseCommandLine(line_buffer, command, args);
        RouteCommand(command, args);

        line_buffer[0] = '\0';
        command[0] = '\0';
        args[0] = '\0';
    }

    ClearRegisteredProducts();

    exit(EXIT_SUCCESS);
}