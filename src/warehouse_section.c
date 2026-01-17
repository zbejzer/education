#include <stdlib.h>

#include "config.h"
#include "warehouse_section.h"

void WarehouseSectionInit(WarehouseSection *obj)
{
    obj->category = UINT_MAX;
    obj->subcategory = UINT_MAX;
    obj->stock_max = UINT_MAX;
    obj->stock_min_threshold = 0;
}

void WarehouseSectionListInit(WarehouseSectionList *obj)
{
    obj->data = NULL;
    obj->size = 0;
}

WarehouseSection *WarehouseSectionListGetSection(const WarehouseSectionList *list, unsigned int category)
{
    for (size_t i = 0; i < list->size; i++)
    {
        if (list->data[i].category == category && list->data[i].subcategory == SUBCATEGORY_WILDCARD)
        {
            return &list->data[i];
        }
    }

    return NULL;
}

WarehouseSection *WarehouseSectionListGetSubsection(const WarehouseSectionList *list, unsigned int category,
                                                    unsigned int subcategory)
{
    for (size_t i = 0; i < list->size; i++)
    {
        if (list->data[i].category == category && list->data[i].subcategory == subcategory)
        {
            return &list->data[i];
        }
    }

    return NULL;
}
