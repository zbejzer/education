#include <string.h>

#include "input_processor.h"

void SanitizeRawLine(char *str)
{
    char *padding = strrchr(str, '\n');
    if (padding != NULL)
    {
        *padding = '\0';
    }
}

void ParseCommandLine(const char *str, char *cmd, char *args)
{
    char *delimiter_pos = strchr(str, ' ');
    if (delimiter_pos != NULL)
    {
        size_t command_length = delimiter_pos - str;
        strncpy(cmd, str, command_length);
        cmd[command_length] = '\0';
        strcpy(args, delimiter_pos + 1);
    }
    else
    {
        strcpy(cmd, str);
        args[0] = '\0';
    }
}

void ParseLineCount(const char *str, unsigned int *count)
{
    sscanf(str, "%u", count);
}

void ParseProductLine(const char *str, Product *product)
{
    char joint_category_buffer[JOINT_CATEGORY_LEN_MAX + 1] = "";

    sscanf(str,
           "%" XSTR(JOINT_CATEGORY_LEN_MAX) "s %u %" XSTR(PRODUCT_ID_LEN_MAX) "s %" XSTR(PRODUCT_NAME_LEN_MAX) "[^\n]",
           joint_category_buffer, &product->flammability, &product->id, &product->name);

    ParseJointCategory(joint_category_buffer, &product->category, &product->subcategory);
}

void ParseJointCategory(const char *str, unsigned int *category, unsigned int *subcategory)
{
    char *delimiter_pos = strchr(str, '.');
    if (delimiter_pos == NULL)
    {
        sscanf(str, "%u", category);
        *subcategory = SUBCATEGORY_WILDCARD;
    }
    else
    {
        sscanf(str, "%u", category);
        sscanf(delimiter_pos + 1, "%u", subcategory);
    }
}
