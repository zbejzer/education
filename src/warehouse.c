#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "warehouse.h"

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

void WarehouseUpdateProduct(Warehouse *warehouse, Product *product, int stock_change)
{
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