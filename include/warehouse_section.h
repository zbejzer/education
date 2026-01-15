#ifndef WHS_WAREHOUSE_SECTION_H_
#define WHS_WAREHOUSE_SECTION_H_

#include "product.h"

typedef struct WarehouseSection
{
    unsigned int stock_max;
    unsigned int stock_min_threshold;
    unsigned int category;
    unsigned int subcategory;
} WarehouseSection;

typedef struct WarehouseSectionList
{
    WarehouseSection *data;
    size_t size;
} WarehouseSectionList;

void WarehouseSectionInit(WarehouseSection *obj);

void WarehouseSectionListInit(WarehouseSectionList *obj);
WarehouseSection *WarehouseSectionListGetSection(WarehouseSectionList *list, unsigned int category);
WarehouseSection *WarehouseSectionListGetSubsection(WarehouseSectionList *list, unsigned int category,
                                                    unsigned int subcategory);

#endif
