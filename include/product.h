#ifndef WAREHOUSE_PRODUCT_H_
#define WAREHOUSE_PRODUCT_H_

#include <stdbool.h>

#include "config.h"

typedef struct Product
{
    char id[PRODUCT_ID_SIZE];
    char name[PRODUCT_NAME_SIZE];
    int stock;
} Product;

Product *ProductGetById(const char *id);
bool IsProductIdExists(const char *id);

#endif