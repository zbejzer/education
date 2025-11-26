#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command_parser.h"
#include "config.h"
#include "product.h"
#include "render.h"
#include "shared.h"

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
    int lines_count = 0;
    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        fscanf(file, "%d", &lines_count);

        for (int i = 0; i < lines_count; i++)
        {
            Product new_product;

            fscanf(file, "%s", new_product.id);
            fscanf(file, " %" XSTR(PRODUCT_NAME_SIZE) "[^\n]", new_product.name);
            new_product.stock = 0;

            kProductCount++;
            kProducts = realloc(kProducts, kProductCount * sizeof(Product));
            memcpy(&(kProducts[kProductCount - 1]), &new_product, sizeof(Product));
        }

        fclose(file);
    }
}

void WarehouseUpdate(const char *filename)
{
    int lines_count = 0;
    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        fscanf(file, "%d", &lines_count);

        for (int i = 0; i < lines_count; i++)
        {
            Product *product_to_update = NULL;
            char product_id[PRODUCT_ID_SIZE] = "";
            char operation[2] = "";
            int stock_change = 0;

            fscanf(file, "%s %1s %d", product_id, operation, &stock_change);
            product_to_update = ProductGetById(product_id);

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
}

void WarehousePrint(const char *base_filename)
{
    FILE *file = NULL;
    char full_filename[FILENAME_MAX];

    if (kPdfMode)
    {
        sprintf(full_filename, "%s.tex", base_filename);
    }
    else
    {
        sprintf(full_filename, "%s.txt", base_filename);
    }

    file = fopen(full_filename, "w");

    if (file != NULL)
    {
        if (kPdfMode)
        {
            RenderPdf(file);
        }
        else
        {
            RenderTxt(file);
        }
        fclose(file);
    }
}

void WarehouseSave()
{
    FILE *file = fopen(SAVE_FILENAME, "w");

    for (int i = 0; i < kProductCount; i++)
    {
        fprintf(file, "%s;\t%s;\t%d\n", kProducts[i].id, kProducts[i].name, kProducts[i].stock);
    }

    fclose(file);
}