#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "warehouse.h"

void WarehouseAddSection(Warehouse *warehouse, const WarehouseSection *section)
{
    return;
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

WarehouseList kWarehouses;