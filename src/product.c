#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "product.h"

Product *ProductGetById(char id[PRODUCT_ID_SIZE])
{
    for (int i = 0; i < kProductCount; i++)
    {
        if (strcmp(kProducts[i].id, id) == 0)
        {
            return &(kProducts[i]);
        }
    }

    return NULL;
}