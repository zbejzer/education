#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"

void ProductInit(Product *obj)
{
    obj->id[0] = '\0';
    obj->name[0] = '\0';
    obj->category = UINT_MAX;
    obj->subcategory = UINT_MAX;
    obj->flammability = UINT_MAX;
}

int ProductCopy(Product *dst, const Product *src)
{
    dst->category = src->category;
    dst->subcategory = src->subcategory;
    dst->flammability = src->flammability;
    strcpy(dst->id, src->id);
    strcpy(dst->name, src->name);

    return 0;
}

void ProductListInit(ProductList *obj)
{
    obj->data = NULL;
    obj->size = 0;
}

Product *ProductListGetById(const char *product_id)
{
    for (size_t i = 0; i < kProducts.size; i++)
    {
        if (strcmp(kProducts.data[i].id, product_id) == 0)
        {
            return &kProducts.data[i];
        }
    }

    return NULL;
}

int ProductListClear()
{
    free(kProducts.data);
    kProducts.data = NULL;
    kProducts.size = 0;

    return 0;
}

int ProductListIsClear(const ProductList *list)
{
    if (list->data != NULL)
    {
        return 1;
    }

    return 0;
}

ProductList kProducts;