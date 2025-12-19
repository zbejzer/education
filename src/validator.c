#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "shared.h"
#include "validator.h"

void ValidateWarehouseSize(int products)
{
    if (products > WAREHOUSE_SIZE_MAX || products < WAREHOUSE_SIZE_MIN)
    {
        fprintf(stderr, "Warehouse size outside of allowed range. Allowed range: %d - %d", WAREHOUSE_SIZE_MIN,
                WAREHOUSE_SIZE_MAX);
        exit(EXIT_FAILURE);
    }

    return;
}

void ValidateWarehouseInitialized()
{
    if (kProducts == NULL)
    {
        fprintf(stderr, "Warehouse hasn't been initialized yet!");
        exit(EXIT_FAILURE);
    }

    return;
}

void ValidateWarehouseNotInitialized()
{
    if (kProducts != NULL)
    {
        fprintf(stderr, "Warehouse has been already initialized!");
        exit(EXIT_FAILURE);
    }

    return;
}

void ValidateProductId(char *str)
{
    if (strlen(str) != PRODUCT_ID_SIZE - 1)
    {
        fprintf(stderr, "Product ID length not allowed! Expected length: %d", PRODUCT_ID_SIZE - 1);
        exit(EXIT_FAILURE);
    }

    if (!isupper(str[0]) || !isupper(str[1]) || !isdigit(str[2]) || !isdigit(str[3]) || !isdigit(str[4]))
    {
        fprintf(stderr, "Incorrect product ID format!");
        exit(EXIT_FAILURE);
    }

    return;
}