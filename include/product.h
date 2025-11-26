#ifndef WAREHOUSE_PRODUCT_H_
#define WAREHOUSE_PRODUCT_H_

#include <stdio.h>

#define PRODUCT_ID_SIZE 6 // 5 chars + null character
#define PRODUCT_NAME_SIZE 128

typedef struct Product
{
    char id[PRODUCT_ID_SIZE];
    char *name;
    int stock;
} Product;

Product ProductCreate(char *id_, char *name_);
void ProductDelete(Product *product_);

#endif