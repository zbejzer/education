#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "warehouse.h"
#include "warehouse_section.h"

void WarehouseListInit(WarehouseList *obj)
{
    obj->front = NULL;
    obj->back = NULL;
    obj->size = 0;
}

int WarehouseListPush(WarehouseNode *new_node)
{
    WarehouseNode *last_node = kWarehouses.back;
    new_node->next = NULL;

    if (last_node == NULL)
    {
        kWarehouses.front = new_node;
    }
    else
    {
        last_node->next = new_node;
    }

    kWarehouses.back = new_node;
    kWarehouses.size++;

    return 0;
}

Warehouse *WarehouseListGetById(const char *warehouse_id)
{
    WarehouseNode *node = kWarehouses.front;

    while (node != NULL)
    {
        if (strcmp(node->data.id, warehouse_id) == 0)
        {
            return &node->data;
        }

        node = node->next;
    }

    return NULL;
}

int WarehouseListClear()
{
    WarehouseNode *node = kWarehouses.front;

    while (node != NULL)
    {
        WarehouseNode *next_node = node->next;
        free(node);
        node = next_node;
    }

    kWarehouses.front = NULL;
    kWarehouses.back = NULL;
    kWarehouses.size = 0;

    return 0;
}

void WarehouseInit(Warehouse *obj)
{
    obj->id[0] = '\0';
    obj->name[0] = '\0';
    obj->stock_max = UINT_MAX;
    obj->flammability_max = UINT_MAX;
    WarehouseSectionListInit(&obj->sections);
    ProductStockListInit(&obj->products);
}

int WarehouseUpdateProduct(Warehouse *warehouse, Product *product, const int stock_change)
{
    ProductStock *product_stock = ProductStockListGetByProduct(&warehouse->products, product);
    WarehouseSection *warehouse_category = NULL;
    WarehouseSection *warehouse_subcategory = NULL;

    if (product_stock == NULL)
    {
        ProductStock new_product_stock;
        ProductStockInit(&new_product_stock);
        new_product_stock.product = product;
        ProductStockListPush(&warehouse->products, &new_product_stock);
    }

    // Warehouse-wide checks

    if (stock_change < 0 && product_stock->stock < (unsigned int)(-stock_change))
    {
        fprintf(stderr, "Insufficient stock for product ID %s to remove %d units!\n", product_stock->product->id,
                -stock_change);
        return 1;
    }

    if (product->flammability > warehouse->flammability_max)
    {
        fprintf(stderr, "Product with ID %s exceeds warehouse max flammability(%d)!\n", product_stock->product->id,
                warehouse->flammability_max);
        return 1;
    }

    if (stock_change + ProductStockListGetTotalStock(&warehouse->products) > warehouse->stock_max)
    {
        fprintf(stderr, "New stock(%d) for product with ID %s exceeds warehouse max capacity(%d)!\n",
                stock_change + product_stock->stock, product_stock->product->id, warehouse->stock_max);
        return 1;
    }

    // Category-wide checks

    warehouse_category = WarehouseSectionListGetCategory(&warehouse->sections, product->category);

    if (warehouse_category == NULL)
    {
        fprintf(stderr, "No suitable category(%d) for product with ID %s!\n", warehouse_category->category,
                product_stock->product->id);
        return 1;
    }

    if (stock_change + warehouse_category->stock_current > warehouse_category->stock_max)
    {
        fprintf(stderr, "New stock(%d) for product with ID %s exceeds %d category limit(%d)!\n",
                stock_change + product_stock->stock, product_stock->product->id, warehouse_category->category,
                warehouse->stock_max);
        return 1;
    }

    // Subcategory-wide checks

    if (product->subcategory != SUBCATEGORY_WILDCARD)
    {
        warehouse_subcategory =
            WarehouseSectionListGetSubcategory(&warehouse->sections, product->category, product->subcategory);

        if (warehouse_subcategory == NULL)
        {
            fprintf(stderr, "No suitable subcategory(%d.%d) for product with ID %s!\n", warehouse_subcategory->category,
                    warehouse_category->subcategory, product_stock->product->id);
            return 1;
        }

        if (stock_change + warehouse_subcategory->stock_current > warehouse_subcategory->stock_max)
        {
            fprintf(stderr, "New stock(%d) for product with ID %s exceeds %d.%d subcategory limit(%d)!\n",
                    stock_change + product_stock->stock, product_stock->product->id, warehouse_subcategory->category,
                    warehouse_subcategory->subcategory, warehouse->stock_max);
            return 1;
        }
    }

    product_stock->stock += stock_change;
    warehouse_category->stock_current += stock_change;
    if (warehouse_subcategory != NULL)
    {
        warehouse_subcategory->stock_current += stock_change;
    }

    return 0;
}

int WarehouseSave()
{
    // FILE *file = fopen(SAVE_FILENAME, "w");

    // if (file == NULL)
    // {
    //    fprintf(stderr, "Failed to save warehouse!\n");
    //     return 1;
    // }

    // ProductNode *node = kProductsRegistry;
    // while (node != NULL)
    // {
    //     fprintf(file, "%s;\t%s;\t%d\n", node->product->id, node->product->name, node->product->stock);
    //     node = node->next;
    // }

    // fclose(file);
    // return 0;

    return 0;
}

void WarehouseNodeInit(WarehouseNode *obj)
{
    obj->next = NULL;
    WarehouseInit(&obj->data);
}

WarehouseList kWarehouses;