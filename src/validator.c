#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "product.h"
#include "validator.h"
#include "warehouse.h"

// TODO: Change return values to a typedef error type acting as bit flags

int ValidateProductsCount(const int count)
{
    if (count > PRODUCTS_COUNT_MAX || count < PRODUCTS_COUNT_MIN)
    {
        return 1;
    }

    return 0;
}

int ValidateProductId(const char *id)
{
    if (strlen(id) != PRODUCT_ID_LEN_MAX)
    {
        return 1;
    }

    if (!isupper(id[0]) || !isupper(id[1]) || !isdigit(id[2]) || !isdigit(id[3]) || !isdigit(id[4]))
    {
        return 1;
    }

    return 0;
}

int ValidateProductName(const char *str)
{
    if (isalpha(str[0]))
    {
        unsigned int str_len = strlen(str);

        for (size_t i = 0; i < str_len; i++)
        {
            if (!isalnum(str[i]) && !isspace(str[i]))
            {
                return 1;
            }
        }

        return 0;
    }

    return 1;
}

int ValidateWarehouseSectionCount(const int count)
{
    if (count > WAREHOUSE_SECTIONS_COUNT_MAX || count < WAREHOUSE_SECTIONS_COUNT_MIN)
    {
        return 1;
    }

    return 0;
}

int ValidateWarehouseId(const char *str)
{
    return ValidateProductId(str);
}

int ValidateWarehouseName(const char *str)
{
    return ValidateProductName(str);
}

int ValidateFilename(const char *str)
{
    if (str[0] == '\0')
    {
        return 1;
    }

    return 0;
}
