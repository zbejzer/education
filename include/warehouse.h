#ifndef WHS_WAREHOUSE_H_
#define WHS_WAREHOUSE_H_

#include "config.h"
#include "product_stock.h"
#include "warehouse_section.h"

typedef struct Warehouse
{
    char id[WAREHOUSE_ID_LEN_MAX + 1];
    char name[WAREHOUSE_NAME_LEN_MAX + 1];
    unsigned int stock_max;
    unsigned int flammability_max;
    WarehouseSectionList sections;
    ProductStockList products;
} Warehouse;

typedef struct WarehouseNode
{
    struct WarehouseNode *next;
    Warehouse data;
} WarehouseNode;

typedef struct WarehouseList
{
    WarehouseNode *front;
    WarehouseNode *back;
    size_t size;
} WarehouseList;

void WarehouseInit(Warehouse *obj);
int WarehouseUpdateProduct(Warehouse *warehouse, Product *product, const int stock_change);
int WarehouseSave(Warehouse *obj);
int WarehouseClear(Warehouse *obj);

void WarehouseNodeInit(WarehouseNode *obj);

void WarehouseListInit(WarehouseList *obj);
int WarehouseListPush(WarehouseNode *new_node);
Warehouse *WarehouseListGetById(const char *warehouse_id);
int WarehouseListClear(WarehouseList *list);
int WarehouseListIsClear(const WarehouseList *list);

extern WarehouseList kWarehouses;

#endif