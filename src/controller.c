#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "controller.h"
#include "file_handler.h"
#include "product.h"
#include "render.h"
#include "validator.h"

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

void RouteCommand(const char *cmd, const char *args)
{
    if (strcmp(cmd, "init") == 0)
    {
        HandleCommandInit(args);
    }
    else if (strcmp(cmd, "create") == 0)
    {
        HandleCommandCreate(args);
    }
    else if (strcmp(cmd, "update") == 0)
    {
        HandleCommandUpdate(args);
    }
    else if (strcmp(cmd, "transfer") == 0)
    {
        HandleCommandTransfer(args);
    }
    else if (strcmp(cmd, "print") == 0)
    {
        HandleCommandPrint(args);
    }
    else
    {
        fprintf(stderr, "Command %s not recognized!\n", cmd);
        fprintf(stderr, "Provided arguments: %s\n", args);
        exit(EXIT_FAILURE);
    }
}

void HandleCommandInit(const char *filename)
{
    FILE *file = NULL;
    int items_count = 0;

    if (!ValidateProductsInitialized(kProductsRegistry))
    {
        fprintf(stderr, "Warehouse already initialized!\n");
        exit(EXIT_FAILURE);
    }

    file = OpenFile(filename, "r");
    fscanf(file, "%d", &items_count);

    if (ValidateWarehouseSize(items_count))
    {
        fprintf(stderr, "Warehouse size outside of allowed range. Allowed range: %d - %d\n", WAREHOUSE_SIZE_MIN,
                WAREHOUSE_SIZE_MAX);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < items_count; i++)
    {
        Product new_product;
        fscanf(file, "%s", new_product.id);
        if (ValidateProductId(new_product.id))
        {
            fprintf(stderr, "Invalid product ID: %s\n", new_product.id);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        if (GetProductById(new_product.id) != NULL)
        {
            fprintf(stderr, "Product with ID %s already exists!\n", new_product.id);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        fscanf(file, " %" XSTR(NAME_ALLOCATED_SIZE) "[^\n]", new_product.name);
        if (ValidateProductName(new_product.name))
        {
            fprintf(stderr, "Invalid product name: %s\n", new_product.name);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        new_product.stock = 0;

        if (AddProductToRegistry(&new_product))
        {
            fprintf(stderr, "Failed to add product with ID %s to warehouse!\n", new_product.id);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
}

void HandleCommandCreate(const char *args)
{
    return;
}

void HandleCommandUpdate(const char *filename)
{
    FILE *file = NULL;
    int items_count = 0;

    if (kProductsRegistry == NULL)
    {
        fprintf(stderr, "Warehouse has not been initialized yet!\n");
        exit(EXIT_FAILURE);
    }

    file = OpenFile(filename, "r");

    fscanf(file, "%d", &items_count);

    for (int i = 0; i < items_count; i++)
    {
        char product_id[ID_ALLOCATED_SIZE] = "";
        char operation[2] = "";
        int stock_change = 0;

        fscanf(file, "%s %1s %d", product_id, operation, &stock_change);

        if (ValidateProductId(product_id))
        {
            fprintf(stderr, "Invalid product ID: %s\n", product_id);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        if (strcmp(operation, "-") == 0)
        {
            stock_change = -1 * stock_change;
        }

        if (UpdateProduct(product_id, stock_change))
        {
            fprintf(stderr, "Failed to update product with ID %s!\n", product_id);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }
}

void HandleCommandTransfer(const char *args)
{
    return;
}

void HandleCommandPrint(const char *base_filename)
{
    FILE *file = NULL;
    char filename[FILENAME_MAX] = "";

    if (ValidateProductsInitialized(kProductsRegistry))
    {
        fprintf(stderr, "Warehouse not initialized!\n");
        exit(EXIT_FAILURE);
    }

    if (kPdfMode)
    {
        sprintf(filename, "%s.tex", base_filename);
    }
    else
    {
        sprintf(filename, "%s.txt", base_filename);
    }

    file = OpenFile(filename, "w");

    if (kPdfMode)
    {
        RenderPdf(file);
    }
    else
    {
        RenderTxt(file);
    }

    printf("%s\n", filename);

    CloseFile(file);
}