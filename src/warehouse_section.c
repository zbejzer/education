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

int WarehouseSectionListReserve(WarehouseSectionList *list, size_t new_cap)
{
    WarehouseSection *new_data = (WarehouseSection *)realloc(list->data, sizeof(WarehouseSection) * new_cap);

    if (new_data == NULL)
    {
        return 1;
    }

    list->data = new_data;
    list->size = new_cap;

    return 0;
}

// TODO: Cover with unit tests
unsigned int WarehouseSectionListGetSectionsTotalStockThreshold(const WarehouseSectionList *list)
{
    unsigned int total_stock_threshold = 0;

    for (size_t i = 0; i < list->size; i++)
    {
        if (list->data[i].subcategory == SUBCATEGORY_WILDCARD)
        {
            total_stock_threshold += list->data[i].stock_min_threshold;
        }
    }

    return total_stock_threshold;
}

// TODO: Cover with unit tests
unsigned int WarehouseSectionListGetSubsectionsTotalStockThreshold(const WarehouseSectionList *list,
                                                                   const unsigned int category)
{
    unsigned int total_stock_threshold = 0;

    for (size_t i = 0; i < list->size; i++)
    {
        if (list->data[i].category == category && list->data[i].subcategory != SUBCATEGORY_WILDCARD)
        {
            total_stock_threshold += list->data[i].stock_min_threshold;
        }
    }

    return total_stock_threshold;
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

int WarehouseSectionListClear(WarehouseSectionList *list)
{
    free(list->data);
    list->data = NULL;
    list->size = 0;

    return 0;
}

int WarehouseSectionListIsClear(const WarehouseSectionList *list)
{
    if (list->data != NULL)
    {
        return 1;
    }

    return 0;
}
