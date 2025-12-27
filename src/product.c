#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"

int ProductCopy(Product *dst, const Product *src)
{
    dst->category = src->category;
    dst->subcategory = src->subcategory;
    dst->flammability = src->flammability;
    strcpy(dst->id, src->id);
    strcpy(dst->name, src->name);

    return 0;
}

Product *ProductGetById(const char *product_id)
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

int ProductUpdate(Product *product, const int stock_change)
{
    // if (stock_change < 0 && product->stock < (unsigned int)(-stock_change))
    // {
    //     fprintf(stderr, "Insufficient stock for product ID %s to remove %d units!\n", product->id, -stock_change);
    //     return 1;
    // }

    // product->stock += stock_change;
    return 0;
}

int ProductListClear()
{
    free(kProducts.data);
    kProducts.data = NULL;
    kProducts.size = 0;

    return 0;
}

ProductList kProducts;