#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "product.h"

Product *ProductGetById(char id[PRODUCT_ID_SIZE])
{
    for (int i = 0; i < product_count; i++)
    {
        if (strcmp(products[i].id, id) == 0)
        {
            return &(products[i]);
        }
    }

    return NULL;
}