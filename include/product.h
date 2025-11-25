#ifndef WAREHOUSE_PRODUCT_H_
#define WAREHOUSE_PRODUCT_H_

#include <stdio.h>

typedef struct Product
{
    char *id;
    char *name;
} Product;

Product ProductCreate(char *id_, char *name_);
void ProductUpdateName(Product *product_);

#endif