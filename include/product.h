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
    ProductStockNode *front;
    ProductStockNode *back;
    size_t size;
} ProductStockList;

void ProductInit(Product *obj);
int ProductCopy(Product *dst, const Product *src);

void ProductListInit(ProductList *obj);
Product *ProductListGetById(const char *product_id);
int ProductListClear();

void ProductStockInit(ProductStock *obj);
int ProductStockUpdate(ProductStock *product_stock, const int stock_change);

void ProductStockNodeInit(ProductStockNode *obj);

void ProductStockListInit(ProductStockList *obj);
ProductStockNode *ProductStockListGetByProduct(ProductStockList *list, Product *prod);
int ProductStockListUpdate(ProductStockList *list, Product *prod, const int stock_change);
ProductStockNode *ProductStockListPush(ProductStockList *list, ProductStock *new_stock);

extern ProductList kProducts;

#endif