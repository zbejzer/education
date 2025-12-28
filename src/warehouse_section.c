#include <stdlib.h>

#include "warehouse_section.h"

void WarehouseSectionInit(WarehouseSection *obj)
{
    obj->category = UINT_MAX;
    obj->subcategory = UINT_MAX;
    obj->current_stock = 0;
    obj->stock_max = UINT_MAX;
    obj->stock_min_threshold = 0;
}

void WarehouseSectionListInit(WarehouseSectionList *obj)
{
    obj->data = NULL;
    obj->size = 0;
}

void AddProductToSection(WarehouseSection *section, const Product *product)
{
    return;
}