#ifndef WAREHOUSE_PRODUCT_H_
#define WAREHOUSE_PRODUCT_H_

#include <stdio.h>

#include "common.h"

typedef struct Product
{
    char id[PRODUCT_ID_SIZE];
    char *name;
    int stock;
} Product;

Product ProductCreate(char *id_, char *name_);
void ProductDelete(Product *product_);

#endif