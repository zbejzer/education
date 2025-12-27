#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "controller.h"
#include "line_parser.h"
#include "product.h"
#include "render.h"

int main(int argc, char *argv[])
{
    char line_buffer[LINE_BUFFER_LEN_MAX + 1] = "";
    char command[COMMAND_LEN_MAX + 1] = "";
    char args[FILENAME_MAX + 1] = "";
    int error = 0;

    if (argc > 1)
    {
        kPdfMode = (strcmp(argv[1], "pdf") == 0);
    }

    while (scanf("%" XSTR(LINE_BUFFER_LEN_MAX) "[^\n]", line_buffer) != EOF && !error)
    {
        ParseCommandLine(line_buffer, command, args);
        error = RouteCommand(command, args);

        line_buffer[0] = '\0';
        command[0] = '\0';
        args[0] = '\0';
    }

    error = ProductListClear() || error;

    if (error)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}