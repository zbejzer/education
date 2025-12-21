#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "shared.h"
#include "validator.h"

int ValidateWarehouseSize(int warehouse_size)
{
    if (warehouse_size > WAREHOUSE_SIZE_MAX || warehouse_size < WAREHOUSE_SIZE_MIN)
    {
        return 1;
    }

    return 0;
}

int ValidateWarehouseInitialized()
{
    if (kWarehouse == NULL)
    {
        return 1;
    }

    return 0;
}

int ValidateProductId(char *id)
{
    if (strlen(id) != PRODUCT_ID_SIZE - 1)
    {
        return 1;
    }

    if (!isupper(id[0]) || !isupper(id[1]) || !isdigit(id[2]) || !isdigit(id[3]) || !isdigit(id[4]))
    {
        return 1;
    }

    return 0;
}

int ValidateProductName(char *str)
{
    if (isalpha(str[0]))
    {
        unsigned int str_len = strlen(str);

        for (size_t i = 0; i < str_len; i++)
        {
            if (!isalnum(str[i]) && !isspace(str[i]))
            {
                break;
            }
        }

        return 0;
    }

    fprintf(stderr, "Incorrect product name!\n");
    exit(EXIT_FAILURE);

    return 1;
}
