#ifndef WHS_WAREHOUSE_H_
#define WHS_WAREHOUSE_H_

#include "product.h"

typedef struct WarehouseNode
{
    struct WarehouseNode *next;
    Product *product;
} WarehouseNode;

int AddWarehouseItem(const Product *product);
int UpdateWarehouseItem(const char *product_id, const int stock_change);
size_t GetWarehouseSize();
Product *GetWarehouseItemById(const char *product_id);
int SaveWarehouse();
int ClearWarehouse();

#endif