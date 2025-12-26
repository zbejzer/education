#ifndef WHS_WAREHOUSE_H_
#define WHS_WAREHOUSE_H_

#include "config.h"
#include "warehouse_section.h"

typedef struct Warehouse
{
    char id[WAREHOUSE_ID_LEN_MAX + 1];
    char name[WAREHOUSE_NAME_LEN_MAX + 1];
    unsigned int max_stock;
    unsigned int max_categories;
    unsigned int flammability;
    WarehouseSectionList sections;
} Warehouse;

typedef struct WarehouseNode
{
    struct WarehouseNode *next;
    Warehouse data;
} WarehouseNode;

typedef struct WarehouseList
{
    WarehouseNode *front;
    size_t size;
} WarehouseList;

void WarehouseAddSection(Warehouse *warehouse, const WarehouseSection *section);
int WarehouseSave();

extern WarehouseList kWarehouses;

#endif