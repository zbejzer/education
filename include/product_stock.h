#ifndef WHS_PRODUCT_STOCK_H_
#define WHS_PRODUCT_STOCK_H_

#include <stdlib.h>

#include "product.h"

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

void ProductStockInit(ProductStock *obj);
int ProductStockUpdate(ProductStock *product_stock, const int stock_change);

void ProductStockNodeInit(ProductStockNode *obj);

void ProductStockListInit(ProductStockList *obj);
ProductStockNode *ProductStockListGetByProduct(ProductStockList *list, Product *prod);
int ProductStockListUpdate(ProductStockList *list, Product *prod, const int stock_change);
ProductStockNode *ProductStockListPush(ProductStockList *list, ProductStock *new_stock);

#endif