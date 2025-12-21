#ifndef WHS_WAREHOUSE_H_
#define WHS_WAREHOUSE_H_

#include "product.h"

typedef struct WarehouseNode
{
    struct WarehouseNode *next;
    Product *product;
} WarehouseNode;

int AddWarehouseItem(Product *product);
int UpdateWarehouseItem(const char *product_id, int stock_change);
size_t GetWarehouseSize();
Product *GetWarehouseItemById(const char *product_id);
void SaveWarehouse();

#endif