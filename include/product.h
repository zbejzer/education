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

void ProductInit(Product *obj);
int ProductCopy(Product *dst, const Product *src);
int ProductUpdate(Product *product, const int stock_change);

void ProductListInit(ProductList *obj);
Product *ProductListGetById(const char *product_id);
int ProductListClear();

void ProductStockInit(ProductStock *obj);

void ProductStockNodeInit(ProductStockNode *obj);

void ProductStockListInit(ProductStockList *obj);

extern ProductList kProducts;

#endif