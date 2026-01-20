#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "controller.h"
#include "guards.h"
#include "input_handler.h"
#include "input_processor.h"
#include "product.h"
#include "product_stock.h"
#include "render.h"
#include "state_save.h"
#include "validator.h"

int RouteCommand(const char *cmd, const char *args)
{
    int ret = 0;

    if (strcmp(cmd, "init") == 0)
    {
        ret = ret || InputStreamDetect(args, "r");
        ret = ret || HandleCommandInit();
        ret = ret || StateSave(&kProducts, &kWarehouses);
    }
    else if (strcmp(cmd, "create") == 0)
    {
        ret = ret || InputStreamDetect(args, "r");
        ret = ret || HandleCommandCreate(args);
        ret = ret || StateSave(&kProducts, &kWarehouses);
    }
    else if (strcmp(cmd, "update") == 0)
    {
        ret = ret || InputStreamDetect(args, "r");
        ret = ret || HandleCommandUpdate();
        ret = ret || StateSave(&kProducts, &kWarehouses);
    }
    else if (strcmp(cmd, "transfer") == 0)
    {
        ret = ret || InputStreamDetect(args, "r");
        ret = ret || HandleCommandTransfer();
        ret = ret || StateSave(&kProducts, &kWarehouses);
    }
    else if (strcmp(cmd, "print") == 0)
    {
        ret = ret || HandleCommandPrint(args);
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
    int products_count = 0;
    char line_buffer[LINE_BUFFER_LEN_MAX + 1] = "";

    if (!ProductListIsClear(&kProducts))
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

    if (ProductListReserve(&kProducts, products_count))
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
        ParseInitEntry(line_buffer, &new_product);

        if (ValidateProductId(new_product.id))
        {
            fprintf(stderr, "Invalid product ID: %s\n", new_product.id);
            return 1;
        }

        if (ProductListGetById(new_product.id) != NULL)
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
    char line_buffer[LINE_BUFFER_LEN_MAX + 1] = "";
    int section_count = 0;
    int ret = 0;
    WarehouseSectionList *section_list = NULL;
    WarehouseNode *warehouse_node = malloc(sizeof(WarehouseNode));

    WarehouseNodeInit(warehouse_node);
    section_list = &warehouse_node->data.sections;

    fgets(line_buffer, LINE_BUFFER_LEN_MAX + 1, kInputStream);
    SanitizeRawLine(line_buffer);
    ParseCreateHeader(line_buffer, &warehouse_node->data);

    fgets(line_buffer, LINE_BUFFER_LEN_MAX + 1, kInputStream);
    SanitizeRawLine(line_buffer);
    ParseLineCount(line_buffer, &section_count);

    if (ValidateProductsCount(section_count))
    {
        fprintf(stderr, "Section count outside of allowed range. Allowed range: %d - %d\n",
                WAREHOUSE_SECTIONS_COUNT_MIN, WAREHOUSE_SECTIONS_COUNT_MAX);
        return 1;
    }

    if (WarehouseSectionListReserve(section_list, section_count))
    {
        fprintf(stderr, "Failed to allocate memory for %d warehouse sections!\n", section_count);
        return 1;
    }

    for (size_t i = 0; i < section_count; i++)
    {
        // TODO: Postopone changing data until after validation
        WarehouseSection *section = &section_list->data[i];
        WarehouseSectionInit(section);

        fgets(line_buffer, LINE_BUFFER_LEN_MAX + 1, kInputStream);
        SanitizeRawLine(line_buffer);
        ParseCreateEntry(line_buffer, section);

        ret = CanSectionCapacityFitStockThreshold(section) || ret;
        ret = CanWarehouseFitSectionCapacity(section, &warehouse_node->data) || ret;
    }

    ret = ret || CanWarehouseFitTotalStockThreshold(&warehouse_node->data);
    ret = ret || CanAllSectionsFitSubsections(&warehouse_node->data.sections);
    ret = ret || CanAllSectionsFitSubsectionsTotalStockThreshold(&warehouse_node->data.sections);

    if (ret == 0)
    {
        ret = WarehouseListPush(warehouse_node) || ret;
    }
    else
    {
        free(warehouse_node);
        warehouse_node = NULL;
    }

    return ret;
}

int HandleCommandUpdate()
{
    char line_buffer[LINE_BUFFER_LEN_MAX + 1] = "";
    char warehouse_id[WAREHOUSE_ID_LEN + 1] = "";
    unsigned int products_count = 0;
    Warehouse *warehouse = NULL;

    if (ProductListIsClear(&kProducts))
    {
        fprintf(stderr, "Products have not been initialized yet!\n");
        return 1;
    }

    if (WarehouseListIsClear(&kWarehouses))
    {
        fprintf(stderr, "Warehouses have not been initialized yet!\n");
        return 1;
    }

    fgets(line_buffer, LINE_BUFFER_LEN_MAX + 1, kInputStream);
    SanitizeRawLine(line_buffer);
    ParseUpdateHeader(line_buffer, warehouse_id);

    if (ValidateWarehouseId(warehouse_id))
    {
        fprintf(stderr, "Invalid warehouse ID: %s\n", warehouse_id);
        return 1;
    }

    warehouse = WarehouseListGetById(warehouse_id);

    if (warehouse == NULL)
    {
        fprintf(stderr, "Failed to fetch warehouse with ID: %s\n", warehouse_id);
        return 1;
    }

    fgets(line_buffer, LINE_BUFFER_LEN_MAX + 1, kInputStream);
    SanitizeRawLine(line_buffer);
    ParseLineCount(line_buffer, &products_count);

    for (int i = 0; i < products_count; i++)
    {
        char product_id[PRODUCT_ID_LEN_MAX + 1] = "";
        Product *product = NULL;
        char operation = '\0';
        int stock_change = 0;

        fgets(line_buffer, LINE_BUFFER_LEN_MAX + 1, kInputStream);
        SanitizeRawLine(line_buffer);
        ParseUpdateEntry(line_buffer, product_id, &operation, &stock_change);

        if (operation == '-')
        {
            stock_change *= -1;
        }

        if (ValidateProductId(product_id))
        {
            fprintf(stderr, "Invalid product ID: %s\n", product_id);
            return 1;
        }

        product = ProductListGetById(product_id);

        if (product == NULL)
        {
            fprintf(stderr, "Product with ID %s does not exists!\n", product_id);
            return 1;
        }

        if (WarehouseUpdateProduct(warehouse, product, stock_change))
        {
            return 1;
        };
    }

    return 0;
}

int HandleCommandTransfer()
{
    char line_buffer[LINE_BUFFER_LEN_MAX + 1] = "";
    char dst_warehouse_id[WAREHOUSE_ID_LEN + 1] = "";
    char src_warehouse_id[WAREHOUSE_ID_LEN + 1] = "";
    unsigned int products_count = 0;
    Warehouse *dst_warehouse = NULL;
    Warehouse *src_warehouse = NULL;

    if (ProductListIsClear(&kProducts))
    {
        fprintf(stderr, "Products have not been initialized yet!\n");
        return 1;
    }

    if (WarehouseListIsClear(&kWarehouses))
    {
        fprintf(stderr, "Warehouses have not been initialized yet!\n");
        return 1;
    }

    fgets(line_buffer, LINE_BUFFER_LEN_MAX + 1, kInputStream);
    SanitizeRawLine(line_buffer);
    ParseTransferHeader(line_buffer, dst_warehouse_id, src_warehouse_id);

    if (ValidateWarehouseId(dst_warehouse_id))
    {
        fprintf(stderr, "Invalid source warehouse ID: %s\n", dst_warehouse_id);
        return 1;
    }

    if (ValidateWarehouseId(src_warehouse_id))
    {
        fprintf(stderr, "Invalid destination warehouse ID: %s\n", src_warehouse_id);
        return 1;
    }

    dst_warehouse = WarehouseListGetById(dst_warehouse_id);

    if (dst_warehouse == NULL)
    {
        fprintf(stderr, "Failed to fetch warehouse with ID: %s\n", dst_warehouse_id);
        return 1;
    }

    src_warehouse = WarehouseListGetById(src_warehouse_id);

    if (src_warehouse == NULL)
    {
        fprintf(stderr, "Failed to fetch warehouse with ID: %s\n", src_warehouse_id);
        return 1;
    }

    fgets(line_buffer, LINE_BUFFER_LEN_MAX + 1, kInputStream);
    SanitizeRawLine(line_buffer);
    ParseLineCount(line_buffer, &products_count);

    for (int i = 0; i < products_count; i++)
    {
        char product_id[PRODUCT_ID_LEN_MAX + 1] = "";
        Product *product = NULL;
        unsigned int stock_change = 0;

        fgets(line_buffer, LINE_BUFFER_LEN_MAX + 1, kInputStream);
        SanitizeRawLine(line_buffer);
        ParseTransferEntry(line_buffer, product_id, &stock_change);

        if (ValidateProductId(product_id))
        {
            fprintf(stderr, "Invalid product ID: %s\n", product_id);
            return 1;
        }

        product = ProductListGetById(product_id);

        if (product == NULL)
        {
            fprintf(stderr, "Product with ID %s does not exists!\n", product_id);
            return 1;
        }

        if (WarehouseUpdateProduct(dst_warehouse, product, stock_change) ||
            WarehouseUpdateProduct(src_warehouse, product, -((int)stock_change)))
        {
            return 1;
        };
    }

    return 0;
}

int HandleCommandPrint(const char *args)
{
    FILE *file = NULL;
    char base_filename[FILENAME_MAX] = "";
    char filename[FILENAME_MAX] = "";

    // TODO: Replace null when args handling added
    ParsePrintArgs(args, base_filename, NULL);

    if (ProductListIsClear(&kProducts))
    {
        fprintf(stderr, "Products have not been initialized yet!\n");
        return 1;
    }

    if (WarehouseListIsClear(&kWarehouses))
    {
        fprintf(stderr, "Warehouses have not been initialized yet!\n");
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

    if ((file = fopen(filename, "w")) == NULL)
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
        RenderTxt(file, &kWarehouses);
    }

    if (fclose(file) == EOF)
    {
        fprintf(stderr, "Error while saving state\n");
        return 1;
    }

    printf("%s\n", filename);

    return 0;
}