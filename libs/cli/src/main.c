#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "controller.h"
#include "input_processor.h"
#include "product.h"
#include "render.h"
#include "warehouse.h"

int main(int argc, char *argv[])
{
    char line_buffer[LINE_BUFFER_LEN_MAX + 1] = "";
    char command[COMMAND_LEN_MAX + 1] = "";
    char args[COMMAND_ARGS_LEN_MAX + 1] = "";
    int error = 0;

    ProductListInit(&kProducts);
    WarehouseListInit(&kWarehouses);

    if (argc > 1)
    {
        kPdfMode = (strcmp(argv[1], "pdf") == 0);
    }

    while (!error && fgets(line_buffer, LINE_BUFFER_LEN_MAX + 1, stdin) != NULL)
    {
        SanitizeRawLine(line_buffer);
        ParseCommandLine(line_buffer, command, args);
        error = RouteCommand(command, args);

        line_buffer[0] = '\0';
        command[0] = '\0';
        args[0] = '\0';
    }

    error = ProductListClear(&kProducts) || error;
    error = WarehouseListClear(&kWarehouses) || error;

    if (error)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}