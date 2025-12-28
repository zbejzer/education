#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "controller.h"
#include "input_handler.h"
#include "input_processor.h"
#include "product.h"
#include "render.h"
#include "validator.h"

int RouteCommand(const char *cmd, const char *args)
{
    int ret = 0;

    if (strcmp(cmd, "init") == 0)
    {
        ret = ret || InputStreamDetect(args, "r");
        ret = ret || HandleCommandInit();
    }
    else if (strcmp(cmd, "create") == 0)
    {
        ret = ret || InputStreamDetect(args, "r");
        ret = ret || HandleCommandCreate(args);
    }
    else if (strcmp(cmd, "update") == 0)
    {
        ret = ret || InputStreamDetect(args, "r");
        ret = ret || HandleCommandUpdate();
    }
    else if (strcmp(cmd, "transfer") == 0)
    {
        ret = HandleCommandTransfer(args);
    }
    else if (strcmp(cmd, "print") == 0)
    {
        ret = HandleCommandPrint(args);
    }
    else
    {
        fprintf(stderr, "Command %s not recognized!\n", cmd);
        fprintf(stderr, "Provided arguments: %s\n", args);
        ret = 1;
    }

    return InputStreamSwitch(stdin) || ret;
}

int HandleCommandInit()
{
    unsigned int products_count = 0;
    char line_buffer[LINE_BUFFER_LEN_MAX + 1] = "";

    if (ValidateProductsClear(kProducts.data))
    {
        fprintf(stderr, "Product list already initialized!\n");
        return 1;
    }

    fgets(line_buffer, LINE_BUFFER_LEN_MAX + 1, kInputStream);
    SanitizeRawLine(line_buffer);
    ParseLineCount(line_buffer, &products_count);

    if (ValidateProductsCount(products_count))
    {
        fprintf(stderr, "Products count outside of allowed range. Allowed range: %d - %d\n", PRODUCTS_COUNT_MIN,
                PRODUCTS_COUNT_MAX);
        return 1;
    }

    kProducts.size = (size_t)products_count;
    kProducts.data = (Product *)malloc(sizeof(Product) * products_count);

    if (kProducts.data == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for %d products!\n", products_count);
        return 1;
    }

    for (size_t i = 0; i < products_count; i++)
    {
        line_buffer[0] = '\0';
        Product new_product;
        ProductInit(&new_product);

        fgets(line_buffer, LINE_BUFFER_LEN_MAX + 1, kInputStream);
        SanitizeRawLine(line_buffer);
        ParseProductLine(line_buffer, &new_product);

        if (ValidateProductId(new_product.id))
        {
            fprintf(stderr, "Invalid product ID: %s\n", new_product.id);
            return 1;
        }

        if (ProductGetById(new_product.id) != NULL)
        {
            fprintf(stderr, "Product with ID %s already exists!\n", new_product.id);
            return 1;
        }

        if (ValidateProductName(new_product.name))
        {
            fprintf(stderr, "Invalid product name: %s\n", new_product.name);
            return 1;
        }

        if (ProductCopy(&kProducts.data[i], &new_product))
        {
            fprintf(stderr, "Failed to copy product with id: %s\n", new_product.id);
        }
    }

    return 0;
}

int HandleCommandCreate(const char *args)
{
    return 0;
}

int HandleCommandUpdate()
{
    int products_count = 0;

    if (!ValidateProductsClear(kProducts.data))
    {
        fprintf(stderr, "Warehouse has not been initialized yet!\n");
        return 1;
    }

    fscanf(kInputStream, "%d", &products_count);

    for (int i = 0; i < products_count; i++)
    {
        char product_id[PRODUCT_ID_LEN_MAX + 1] = "";
        char operation[2] = "";
        int stock_change = 0;

        fscanf(kInputStream, "%s %1s %d", product_id, operation, &stock_change);

        if (ValidateProductId(product_id))
        {
            fprintf(stderr, "Invalid product ID: %s\n", product_id);
            return 1;
        }

        if (strcmp(operation, "-") == 0)
        {
            stock_change = -1 * stock_change;
        }

        if (ProductUpdate(ProductGetById(product_id), stock_change))
        {
            fprintf(stderr, "Failed to update product with ID %s!\n", product_id);
            return 1;
        }
    }
}

int HandleCommandTransfer(const char *args)
{
    return 0;
}

int HandleCommandPrint(const char *base_filename)
{
    FILE *file = NULL;
    char filename[FILENAME_MAX] = "";

    if (!ValidateProductsClear(kProducts.data))
    {
        fprintf(stderr, "Warehouse not initialized!\n");
        return 1;
    }

    if (kPdfMode)
    {
        sprintf(filename, "%s.tex", base_filename);
    }
    else
    {
        sprintf(filename, "%s.txt", base_filename);
    }

    file = fopen(filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file %s with mode %s\n", filename, "w");
        return 1;
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

    return 0;
}