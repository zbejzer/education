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
    struct WarehouseNode *prev;
    Warehouse warehouse;
} WarehouseNode;

typedef struct WarehouseList
{
    WarehouseNode *front;
    WarehouseNode *back;
    size_t size;
} WarehouseList;

void AddSectionToWarehouse(Warehouse *warehouse, const WarehouseSection *section);
int SaveWarehouse();

extern WarehouseList kWarehouses;

#endif