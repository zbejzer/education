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

void ProductStockNodeInit(ProductStockNode *obj);

void ProductStockListInit(ProductStockList *obj);
unsigned int ProductStockListGetTotalStock(const ProductStockList *list);
unsigned int ProductStockListGetCategoryStock(const ProductStockList *list, const unsigned int category,
                                              const unsigned int subcategory);
ProductStock *ProductStockListGetByProduct(const ProductStockList *list, const Product *prod);
void ProductStockListPush(ProductStockList *list, const ProductStock *product_stock);

#endif