#ifndef WHS_PRODUCT_H_
#define WHS_PRODUCT_H_

#include <stdbool.h>

#include "config.h"

typedef struct Product
{
    char id[PRODUCT_ID_LEN_MAX + 1];
    char name[PRODUCT_NAME_LEN_MAX + 1];
    unsigned int category;
    unsigned int subcategory;
    unsigned int flammability;
} Product;

typedef struct ProductList
{
    Product *data;
    size_t size;
} ProductList;

void ProductInit(Product *obj);
int ProductCopy(Product *dst, const Product *src);

void ProductListInit(ProductList *obj);
Product *ProductListGetById(const char *product_id);
int ProductListClear();

extern ProductList kProducts;

#endif