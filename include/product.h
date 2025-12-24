#ifndef WHS_PRODUCT_H_
#define WHS_PRODUCT_H_

#include <stdbool.h>

#include "config.h"

typedef struct Product
{
    char id[ID_ALLOCATED_SIZE];
    char name[NAME_ALLOCATED_SIZE];
    unsigned int stock;
} Product;

int AddProductToRegistry(const Product *product);
Product *GetProductById(const char *product_id);
int UpdateProduct(Product *product, const int stock_change);
size_t GetRegisteredProductCount();
int ClearRegisteredProducts();

extern Product *kProductsRegistry;

#endif