#include <stdlib.h>
#include <string.h>

#include "product.h"
#include "shared.h"

Product *ProductGetById(const char *id)
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