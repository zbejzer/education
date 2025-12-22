#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "controller.h"
#include "product.h"
#include "render.h"
#include "shared.h"
#include "validator.h"

void HandleCommand(const char *command, const char *args)
{
    if (strcmp(command, "init") == 0)
    {
        CommandInitialize(args);
        if (SaveWarehouse())
        {
            fprintf(stderr, "Failed to save warehouse!\n");
            exit(EXIT_FAILURE);
        }
        }
    else if (strcmp(command, "update") == 0)
    {

        CommandUpdate(args);
        if (SaveWarehouse())
        {
            fprintf(stderr, "Failed to save warehouse!\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (strcmp(command, "print") == 0)
    {
        CommandPrint(args);
    }
}

void CommandInitialize(const char *filename)
{
    if (!ValidateWarehouseInitialized(kWarehouse))
    {
        fprintf(stderr, "Warehouse already initialized!\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int items_count = 0;
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

        if (GetWarehouseItemById(new_product.id) != NULL)
        {
            fprintf(stderr, "Product with ID %s already exists!\n", new_product.id);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        fscanf(file, " %" XSTR(PRODUCT_NAME_SIZE) "[^\n]", new_product.name);
        if (ValidateProductName(new_product.name))
        {
            fprintf(stderr, "Invalid product name: %s\n", new_product.name);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        new_product.stock = 0;

        if (AddWarehouseItem(&new_product))
        {
            fprintf(stderr, "Failed to add product with ID %s to warehouse!\n", new_product.id);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
}

void CommandUpdate(const char *filename)
{
    if (kWarehouse == NULL)
    {
        fprintf(stderr, "Warehouse has not been initialized yet!\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int items_count = 0;
    fscanf(file, "%d", &items_count);

    for (int i = 0; i < items_count; i++)
    {
        char product_id[PRODUCT_ID_SIZE] = "";
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

        if (UpdateWarehouseItem(product_id, stock_change))
        {
            fprintf(stderr, "Failed to update product with ID %s!\n", product_id);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }
}

void CommandPrint(const char *base_filename)
{
    if (ValidateWarehouseInitialized(kWarehouse))
    {
        fprintf(stderr, "Warehouse not initialized!\n");
        exit(EXIT_FAILURE);
    }

    char filename[FILENAME_MAX];

    if (kPdfMode)
    {
        sprintf(filename, "%s.tex", base_filename);
    }
    else
    {
        sprintf(filename, "%s.txt", base_filename);
    }

    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if (kPdfMode)
    {
        RenderPdf(file);
    }
    else
    {
        RenderTxt(file);
    }

    printf("%s\n", filename);
    fclose(file);
}