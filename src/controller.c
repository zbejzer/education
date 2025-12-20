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
        WarehouseInit(args);
        WarehouseSave();
    }
    else if (strcmp(command, "update") == 0)
    {

        WarehouseUpdate(args);
        WarehouseSave();
    }
    else if (strcmp(command, "print") == 0)
    {
        WarehousePrint(args);
    }
}

void WarehouseInit(const char *filename)
{
    if (!ValidateWarehouseInitialized())
    {
        fprintf(stderr, "Warehouse already initialized!\n");
        exit(EXIT_FAILURE);
    }

    int warehouse_size = 0;
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &warehouse_size);

    if (ValidateWarehouseSize(warehouse_size))
    {
        fprintf(stderr, "Warehouse size outside of allowed range. Allowed range: %d - %d\n", WAREHOUSE_SIZE_MIN,
                WAREHOUSE_SIZE_MAX);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < warehouse_size; i++)
    {
        Product new_product;
        fscanf(file, "%s", new_product.id);

        if (ValidateProductId(new_product.id))
        {
            fprintf(stderr, "Invalid product ID: %s\n", new_product.id);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        if (IsProductIdExists(new_product.id))
        {
            fprintf(stderr, "Product with ID %s already exists!\n", new_product.id);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        fscanf(file, " %" XSTR(PRODUCT_NAME_SIZE) "[^\n]", new_product.name);
        new_product.stock = 0;

        kProductCount++;
        kProducts = realloc(kProducts, kProductCount * sizeof(Product));
        memcpy(&(kProducts[kProductCount - 1]), &new_product, sizeof(Product));
    }

    fclose(file);
}

void WarehouseUpdate(const char *filename)
{
    if (kProducts == NULL)
    {
        fprintf(stderr, "Warehouse has not been initialized yet!\n");
        exit(EXIT_FAILURE);
    }

    int lines_count = 0;
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &lines_count);

    for (int i = 0; i < lines_count; i++)
    {
        Product *product_to_update = NULL;
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

        product_to_update = ProductGetById(product_id);

        if (product_to_update == NULL)
        {
            fprintf(stderr, "Product with ID %s does not exist!\n", product_id);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        if (strcmp(operation, "+") == 0)
        {
            product_to_update->stock += stock_change;
        }
        else if (strcmp(operation, "-") == 0)
        {
            if (product_to_update->stock < stock_change)
            {
                fprintf(stderr, "Insufficient stock for product ID %s to remove %d units!\n", product_id, stock_change);
                fclose(file);
                exit(EXIT_FAILURE);
            }

            product_to_update->stock -= stock_change;
        }
    }
}

void WarehousePrint(const char *base_filename)
{
    if (ValidateWarehouseInitialized())
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

void WarehouseSave()
{
    FILE *file = fopen(SAVE_FILENAME, "w");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file: %s\n", SAVE_FILENAME);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < kProductCount; i++)
    {
        fprintf(file, "%s;\t%s;\t%d\n", kProducts[i].id, kProducts[i].name, kProducts[i].stock);
    }

    fclose(file);
}