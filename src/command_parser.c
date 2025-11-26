#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command_parser.h"
#include "common.h"
#include "product.h"

void ParseCommand(char *prompt)
{
    char *space_position = NULL;
    char *command = NULL;
    char *args = NULL;
    size_t command_length = 0;
    size_t args_length = 0;

    if ((space_position = strchr(prompt, ' ')) != NULL)
    {
        command_length = space_position - prompt;
        command = malloc((command_length + 1) * sizeof(char));
        strncpy(command, prompt, command_length);
        command[command_length] = '\0';
        args_length = (strlen(space_position + 1));
        args = malloc((args_length + 1) * sizeof(char));
        strcpy(args, space_position + 1);
    }
    else
    {
        command = malloc((command_length + 1) * sizeof(char));
        strcpy(command, prompt);
    }

    HandleCommand(command, args);

    free(command);
    free(args);
}

void HandleCommand(char *command, char *args)
{
    FILE *file = NULL;

    if (strcmp(command, "init") == 0)
    {
        file = fopen(args, "r");
        if (file != NULL)
        {
            WarehouseInit(file);
            fclose(file);
        }
        WarehouseSave();
    }
    else if (strcmp(command, "update") == 0)
    {
        file = fopen(args, "r");
        if (file != NULL)
        {
            WarehouseUpdate(file);
            fclose(file);
        }
        WarehouseSave();
    }
    else if (strcmp(command, "print") == 0)
    {
        file = fopen(args, "w");
        if (file != NULL)
        {
            WarehousePrint(file);
            fclose(file);
        }
    }
}

void WarehouseInit(FILE *input_file)
{
    int lines_count = 0;

    fscanf(input_file, "%d", &lines_count);

    for (int i = 0; i < lines_count; i++)
    {
        Product new_product;

        fscanf(input_file, "%s", new_product.id);
        fscanf(input_file, " %" STR_PRODUCT_NAME_SIZE "[^\n]", new_product.name);
        new_product.stock = 0;

        product_count++;
        products = realloc(products, product_count * sizeof(Product));
        memcpy(&(products[product_count - 1]), &new_product, sizeof(Product));
    }
}

void WarehouseUpdate(FILE *input_file)
{
    int lines_count = 0;

    fscanf(input_file, "%d", &lines_count);

    for (int i = 0; i < lines_count; i++)
    {
        Product *product_to_update = NULL;
        char id_buffer[PRODUCT_ID_SIZE] = "";
        char operation[2] = "";
        int stock_change = 0;

        fscanf(input_file, "%s", id_buffer);
        fscanf(input_file, " %1s", operation);
        fscanf(input_file, " %d", &stock_change);

        product_to_update = ProductGetById(id_buffer);

        if (strcmp(operation, "+") == 0)
        {
            product_to_update->stock += stock_change;
        }
        else if (strcmp(operation, "-") == 0)
        {
            product_to_update->stock -= stock_change;
        }
    }
}

void WarehousePrint(FILE *output_file)
{
    for (int i = 0; i < product_count; i++)
    {
        printf("%s\t%s\t%d\n", products[i].id, products[i].name, products[i].stock);
    }
}

void WarehouseSave()
{
    WarehousePrint(NULL);
}