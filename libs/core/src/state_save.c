#include <stdio.h>

#include "product.h"
#include "product_stock.h"
#include "render.h"
#include "state_save.h"
#include "warehouse.h"

// TODO: Cover with unit tests
int StateSave(ProductList *products, WarehouseList *warehouses)
{

    FILE *file = NULL;

    if ((file = fopen(SAVE_FILENAME, "w")) == NULL)
    {
        fprintf(stderr, "Error while saving state\n");
        fprintf(stderr, "Could not open file %s\n", SAVE_FILENAME);
        return 1;
    }

    StateSaveRender(file, products, warehouses);

    if (fclose(file) == EOF)
    {
        fprintf(stderr, "Error while saving state\n");
        fprintf(stderr, "Could not close file %s\n", SAVE_FILENAME);
        return 1;
    }

    return 0;
}

// TODO: Cover with unit tests
void StateSaveRender(FILE *stream, ProductList *products, WarehouseList *warehouses)
{
    WarehouseNode *warehouse_node = warehouses->front;

    for (size_t i = 0; i < (*products).size; i++)
    {
        StateSaveRenderProduct(stream, &(*products).data[i]);
    }

    fprintf(stream, "\n");

    while (warehouse_node != NULL)
    {
        StateSaveRenderWarehouse(stream, &warehouse_node->data);
        warehouse_node = warehouse_node->next;
    }
}

// TODO: Cover with unit tests
void StateSaveRenderProduct(FILE *stream, const Product *product)
{
    fprintf(stream, "[Product]\n");
    fprintf(stream, "\tID: %s\n", product->id);
    fprintf(stream, "\tName: %s\n", product->name);
    fprintf(stream, "\tCategory: %u\n", product->category);
    fprintf(stream, "\tSubcategory: ");
    if (product->subcategory == SUBCATEGORY_WILDCARD)
    {
        fprintf(stream, "NULL");
    }
    else
    {
        fprintf(stream, "%u", product->subcategory);
    }
    fprintf(stream, "\n");
    fprintf(stream, "\tFlammability: %u\n", product->flammability);
}

// TODO: Cover with unit tests
void StateSaveRenderWarehouse(FILE *stream, const Warehouse *warehouse)
{
    const WarehouseSectionList *sections = &warehouse->sections;
    const ProductStockNode *product_stock_node = warehouse->products.front;

    fprintf(stream, "[Warehouse]\n");
    fprintf(stream, "\tID: %s\n", warehouse->id);
    fprintf(stream, "\tName: %s\n", warehouse->name);
    fprintf(stream, "\tStock limit: %u\n", warehouse->stock_max);
    fprintf(stream, "\tFlammability limit: %u\n", warehouse->flammability_max);

    if (sections->size > 0)
    {
        fprintf(stream, "[Warehouse Sections]\n");
    }
    for (size_t i = 0; i < sections->size; i++)
    {
        StateSaveRenderSection(stream, &sections->data[i]);
    }

    if (product_stock_node != NULL)
    {
        fprintf(stream, "[Warehouse Product Stock]\n");
    }
    while (product_stock_node != NULL)
    {
        StateSaveRenderProductStock(stream, &product_stock_node->data);
        product_stock_node = product_stock_node->next;
    }
}

// TODO: Cover with unit tests
void StateSaveRenderSection(FILE *stream, const WarehouseSection *section)
{
    fprintf(stream, "[Section]\n");
    fprintf(stream, "\tCategory: %u\n", section->category);
    fprintf(stream, "\tSubcategory: ");
    if (section->subcategory == SUBCATEGORY_WILDCARD)
    {
        fprintf(stream, "NULL");
    }
    else
    {
        fprintf(stream, "%u", section->subcategory);
    }
    fprintf(stream, "\n");
    fprintf(stream, "\tStock limit: %u\n", section->stock_max);
    fprintf(stream, "\tStock minimum threshold: %u\n", section->stock_min_threshold);
}

// TODO: Cover with unit tests
void StateSaveRenderProductStock(FILE *stream, const ProductStock *stock)
{
    fprintf(stream, "[Product Stock]\n");
    fprintf(stream, "\tID: %s\tStock: %u\n", stock->product->id, stock->stock);
}
