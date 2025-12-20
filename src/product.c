#include <stdlib.h>
#include <string.h>

#include "product.h"
#include "shared.h"

Product *ProductGetById(const char *id)
{
    for (size_t i = 0; i < kProductCount; i++)
    {
        if (strcmp(kProducts[i].id, id) == 0)
        {
            return &(kProducts[i]);
        }
    }

    return NULL;
}

bool IsProductIdExists(const char *id)
{
    for (size_t i = 0; i < kProductCount; i++)
    {
        if (strcmp(kProducts[i].id, id) == 0)
        {
            return true;
        }
    }

    return false;
}