#include <string.h>

#include "input_processor.h"

void SanitizeRawLine(char *str)
{
    char *padding = str + strlen(str) - 1;
    if (*padding == '\n')
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

void ParseLineCount(const char *str, int *count)
{
    sscanf(str, "%d", count);
}

void ParseUpdateHeader(const char *str, char *warehouse_id)
{
    sscanf(str, "%s", warehouse_id);
}

void ParseUpdateEntry(const char *str, char *product_id, char *operation, int *stock_change)
{
    sscanf(str, "%" XSTR(PRODUCT_ID_LEN_MAX) "s %c %d", product_id, operation, stock_change);
}

void ParseInitEntry(const char *str, Product *product)
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

void ParseCreateHeader(const char *str, Warehouse *warehouse)
{
    sscanf(str, "%" XSTR(WAREHOUSE_ID_LEN_MAX) "s %u %u %" XSTR(WAREHOUSE_NAME_LEN_MAX) "[^\n]", warehouse->id,
           &warehouse->stock_max, &warehouse->flammability_max, warehouse->name);
}

void ParseCreateEntry(const char *str, WarehouseSection *section)
{
    char joint_category_buffer[JOINT_CATEGORY_LEN_MAX + 1] = "";

    sscanf(str, "%" XSTR(JOINT_CATEGORY_LEN_MAX) "s %u %u", joint_category_buffer, &section->stock_max,
           &section->stock_min_threshold);

    ParseJointCategory(joint_category_buffer, &section->category, &section->subcategory);
}

void ParseTransferHeader(const char *str, char *dst_warehouse_id, char *src_warehouse_id)
{
    sscanf(str, "%s %s", dst_warehouse_id, src_warehouse_id);
}

void ParseTransferEntry(const char *str, char *product_id, unsigned int *stock_change)
{
    sscanf(str, "%s %d", product_id, stock_change);
}

// TODO: Handle flags parsing
void ParsePrintArgs(const char *str, char *filename, char *flags)
{
    sscanf(str, "%s", filename);
}
