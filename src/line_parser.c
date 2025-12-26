#include <string.h>

#include "line_parser.h"

void ParseCommandLine(const char *command_line, char *cmd, char *args)
{
    char *delimiter_pos = strchr(command_line, ' ');
    if (delimiter_pos != NULL)
    {
        size_t command_length = delimiter_pos - command_line;
        strncpy(cmd, command_line, command_length);
        cmd[command_length] = '\0';
        strcpy(args, delimiter_pos + 1);
    }
    else
    {
        strcpy(cmd, command_line);
        args[0] = '\0';
    }
}

void ParseProductLine(const char *product_line, Product *product)
{
    char joint_category_buffer[JOINT_CATEGORY_LEN_MAX + 1] = "";

    sscanf(product_line,
           "%" XSTR(JOINT_CATEGORY_LEN_MAX) "s %u %" XSTR(PRODUCT_ID_LEN_MAX) "s %" XSTR(PRODUCT_NAME_LEN_MAX) "[^\n]",
           joint_category_buffer, &product->flammability, &product->id, &product->name);

    ParseJointCategory(joint_category_buffer, &product->category, &product->subcategory);
}

void ParseJointCategory(const char *joint_category, unsigned int *category, unsigned int *subcategory)
{
    char *delimiter_pos = strchr(joint_category, '.');
    if (delimiter_pos == NULL)
    {
        sscanf(joint_category, "%u", category);
        *subcategory = SUBCATEGORY_WILDCARD;
    }
    else
    {
        sscanf(joint_category, "%u", category);
        sscanf(delimiter_pos + 1, "%u", subcategory);
    }
}
