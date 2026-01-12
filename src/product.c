#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"

void ProductInit(Product *obj)
{
    obj->id[0] = '\0';
    obj->name[0] = '\0';
    obj->category = UINT_MAX;
    obj->subcategory = UINT_MAX;
    obj->flammability = UINT_MAX;
}

int ProductCopy(Product *dst, const Product *src)
{
    dst->category = src->category;
    dst->subcategory = src->subcategory;
    dst->flammability = src->flammability;
    strcpy(dst->id, src->id);
    strcpy(dst->name, src->name);

    return 0;
}

void ProductListInit(ProductList *obj)
{
    obj->data = NULL;
    obj->size = 0;
}

Product *ProductListGetById(const char *product_id)
{
    for (size_t i = 0; i < kProducts.size; i++)
    {
        if (strcmp(kProducts.data[i].id, product_id) == 0)
        {
            return &kProducts.data[i];
        }
    }

    return NULL;
}

int ProductListClear()
{
    free(kProducts.data);
    kProducts.data = NULL;
    kProducts.size = 0;

    return 0;
}

void ProductStockInit(ProductStock *obj)
{
    obj->product = NULL;
    obj->stock = 0;
}

int ProductStockUpdate(ProductStock *product_stock, const int stock_change)
{
    if (stock_change < 0 && product_stock->stock < (unsigned int)(-stock_change))
    {
        fprintf(stderr, "Insufficient stock for product ID %s to remove %d units!\n", product_stock->product->id,
                -stock_change);
        return 1;
    }

    product_stock->stock += stock_change;
    return 0;
}

void ProductStockNodeInit(ProductStockNode *obj)
{
    obj->next = NULL;
    ProductStockInit(&obj->data);
}

void ProductStockListInit(ProductStockList *obj)
{
    obj->front = NULL;
    obj->back = NULL;
    obj->size = 0;
}

ProductStockNode *ProductStockListGetByProduct(ProductStockList *list, Product *prod)
{
    ProductStockNode *node = list->front;

    while (node != NULL)
    {
        if (node->data.product == prod)
        {
            return node;
        }

        node = node->next;
    }

    return node;
}

int ProductStockListUpdate(ProductStockList *list, Product *prod, const int stock_change)
{
    ProductStockNode *node = ProductStockListGetByProduct(list, prod);

    if (node == NULL)
    {
        return 1;
    }

    return ProductStockUpdate(&node->data, stock_change);
}

ProductStockNode *ProductStockListPush(ProductStockList *list, ProductStock *new_stock)
{
    ProductStockNode *last_node = list->back;
    ProductStockNode *new_node = (ProductStockNode *)malloc(sizeof(ProductStockNode));
    ProductStockNodeInit(new_node);

    new_node->next = NULL;

    if (last_node == NULL)
    {
        list->front = new_node;
    }
    else
    {
        last_node->next = new_node;
    }

    list->back = new_node;
    list->size++;

    return new_node;
}

ProductList kProducts;