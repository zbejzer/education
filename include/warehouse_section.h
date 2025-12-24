#ifndef WHS_WAREHOUSE_SECTION_H_
#define WHS_WAREHOUSE_SECTION_H_

#include "product.h"

typedef struct WarehouseSection
{
    unsigned int current_stock;
    unsigned int max_stock;
    unsigned int min_stock_threshold;
    unsigned int category;
    int subcategory; // -1 indicates any
} WarehouseSection;

typedef struct WarehouseSectionNode
{
    struct WarehouseSectionNode *next;
    struct WarehouseSectionNode *prev;
    WarehouseSection section;
} WarehouseSectionNode;

typedef struct WarehouseSectionList
{
    WarehouseSectionNode *front;
    WarehouseSectionNode *back;
    size_t size;
} WarehouseSectionList;

void AddProductToSection(WarehouseSection *section, const Product *product);

#endif
