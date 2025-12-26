#ifndef WHS_PRODUCT_H_
#define WHS_PRODUCT_H_

#include <stdbool.h>

#include "config.h"

typedef struct Product
{
    char id[ID_ALLOCATED_SIZE];
    char name[NAME_ALLOCATED_SIZE];
} Product;

typedef struct ProductList
{
    Product *data;
    size_t size;
} ProductList;

typedef struct ProductStock
{
    Product *product;
    unsigned int stock;
} ProductStock;

typedef struct ProductStockNode
{
    struct ProductStockNode *next;
    ProductStock data;
} ProductStockNode;

typedef struct ProductStockList
{
    ProductStockNode *data;
    size_t size;
} ProductStockList;

Product *ProductGetById(const char *product_id);
int ProductUpdate(Product *product, const int stock_change);
int ProductClearAll();

extern ProductList kProducts;

#endif