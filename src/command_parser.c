#include "command_parser.h"

#include <stdlib.h>
#include <string.h>

void ParseCommand(char *prompt)
{
    char *space_position = NULL;
    char *command = NULL;
    char *args = NULL;
    size_t command_length = 0;

    if ((space_position = strchr(prompt, ' ')) != NULL)
    {
        command_length = space_position - prompt;
        command = malloc((command_length + 1) * sizeof(char));
        strncpy(command, prompt, command_length);
        command[command_length] = '\0';
        args = malloc(strlen(space_position));
        strcpy(args, space_position + 1);
    }
    else
    {
        command = prompt;
    }

    free(command);
    free(args);
}

void WarehouseInit()
{
}

void WarehouseUpdate()
{
}