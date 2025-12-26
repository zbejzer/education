#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"

Product *ProductGetById(const char *product_id)
{
    for (size_t i = 0; i < kProducts.size; i++)
    {
        if (strcmp(kProducts.data[i].id, product_id) == 0)
        {
            return &kProducts.data[i];
        }
    }

    fprintf(stderr, "Product with ID %s does not exist!\n", product_id);
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

int ProductClearAll()
{
    free(kProducts.data);

    return 0;
}

ProductList kProducts;