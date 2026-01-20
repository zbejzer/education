#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "guards.h"
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

int WarehouseListClear(WarehouseList *list)
{
    int ret = 0;
    WarehouseNode *node = list->front;

    while (node != NULL)
    {
        WarehouseNode *next_node = node->next;
        ret = WarehouseClear(&node->data) || ret;
        free(node);
        node = next_node;
    }

    list->front = NULL;
    list->back = NULL;
    list->size = 0;

    return ret;
}

int WarehouseListIsClear(const WarehouseList *list)
{
    if (list->front == NULL)
    {
        return 1;
    }

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

    if (product_stock == NULL)
    {
        if (CanWarehouseTakeProduct(warehouse, product, stock_change))
        {
            return 1;
        }

        ProductStock new_product_stock;
        ProductStockInit(&new_product_stock);
        new_product_stock.product = product;
        ProductStockListPush(&warehouse->products, &new_product_stock);
        product_stock = ProductStockListGetByProduct(&warehouse->products, product);
    }
    else
    {
        if (CanRemoveStock(product_stock, stock_change))
        {
            return 1;
        }
    }

    product_stock->stock += stock_change;

    return 0;
}

// TODO : Update to new architecture
int WarehouseSave(Warehouse *obj)
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

int WarehouseClear(Warehouse *obj)
{
    int ret = 0;

    ret = ProductStockListClear(&obj->products) || ret;
    ret = WarehouseSectionListClear(&obj->sections) || ret;

    return ret;
}

void WarehouseNodeInit(WarehouseNode *obj)
{
    obj->next = NULL;
    WarehouseInit(&obj->data);
}

WarehouseList kWarehouses;