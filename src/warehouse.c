#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shared.h"
#include "warehouse.h"

int AddWarehouseItem(Product *product)
{
    WarehouseNode *new_node = malloc(sizeof(WarehouseNode));
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation for new WarehouseNode failed in AddWarehouseItem!\n");
        return 1;
    }

    new_node->product = malloc(sizeof(Product));
    if (new_node->product == NULL)
    {
        fprintf(stderr, "Memory allocation for new Product failed in AddWarehouseItem!\n");
        return 1;
    }
    memcpy(new_node->product, product, sizeof(Product));

    new_node->next = NULL;

    if (kWarehouse == NULL)
    {
        kWarehouse = new_node;
    }
    else
    {
        WarehouseNode *current_node = kWarehouse;
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }

    return 0;
}

int UpdateWarehouseItem(const char *product_id, int stock_change)
{
    Product *item = GetWarehouseItemById(product_id);
    if (item == NULL)
    {
        fprintf(stderr, "Product with ID %s does not exist!\n", product_id);
        return 1;
    }

    if (stock_change < 0 && item->stock < (unsigned int)(-stock_change))
    {
        fprintf(stderr, "Insufficient stock for product ID %s to remove %d units!\n", product_id, -stock_change);
        return 1;
    }

    item->stock += stock_change;
    return 0;
}

size_t GetWarehouseSize()
{
    size_t size = 0;
    WarehouseNode *node = kWarehouse;

    while (node != NULL)
    {
        size++;
        node = node->next;
    }

    return size;
}

Product *GetWarehouseItemById(const char *product_id)
{
    WarehouseNode *node = kWarehouse;
    while (node != NULL)
    {
        if (strcmp(node->product->id, product_id) == 0)
        {
            return node->product;
        }
        node = node->next;
    }

    return NULL;
}

void SaveWarehouse()
{
    FILE *file = fopen(SAVE_FILENAME, "w");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file: %s\n", SAVE_FILENAME);
        exit(EXIT_FAILURE);
    }

    WarehouseNode *node = kWarehouse;
    while (node != NULL)
    {
        fprintf(file, "%s;\t%s;\t%d\n", node->product->id, node->product->name, node->product->stock);
        node = node->next;
    }

    fclose(file);
}