#ifndef WHS_WAREHOUSE_H_
#define WHS_WAREHOUSE_H_

#include "config.h"
#include "warehouse_section.h"

typedef struct Warehouse
{
    char id[ID_ALLOCATED_SIZE];
    char name[NAME_ALLOCATED_SIZE];
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