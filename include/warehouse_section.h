#ifndef WHS_WAREHOUSE_SECTION_H_
#define WHS_WAREHOUSE_SECTION_H_

#include "product.h"

typedef struct WarehouseSection
{
    unsigned int current_stock;
    unsigned int max_stock;
    unsigned int min_stock_threshold;
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

void AddProductToSection(WarehouseSection *section, const Product *product);

#endif
