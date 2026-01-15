
#include "product_stock.h"
#include "config.h"

void ProductStockInit(ProductStock *obj)
{
    obj->product = NULL;
    obj->stock = 0;
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

unsigned int ProductStockListGetTotalStock(const ProductStockList *list)
{
    unsigned int total_stock = 0;
    ProductStockNode *node = list->front;

    while (node != NULL)
    {
        total_stock += node->data.stock;

        node = node->next;
    }

    return total_stock;
}

unsigned int ProductStockListGetCategoryStock(const ProductStockList *list, const unsigned int category,
                                              const unsigned int subcategory)
{
    unsigned int stock_sum = 0;
    ProductStockNode *node = list->front;

    while (node != NULL)
    {
        if (node->data.product->category == category &&
            (subcategory == SUBCATEGORY_WILDCARD || node->data.product->subcategory == subcategory))
        {
            stock_sum += node->data.stock;
        }

        node = node->next;
    }

    return stock_sum;
}

ProductStock *ProductStockListGetByProduct(const ProductStockList *list, const Product *prod)
{
    ProductStockNode *node = list->front;

    while (node != NULL)
    {
        if (node->data.product == prod)
        {
            return &node->data;
        }

        node = node->next;
    }

    return NULL;
}

void ProductStockListPush(ProductStockList *list, const ProductStock *product_stock)
{
    ProductStockNode *last_node = list->back;
    ProductStockNode *new_node = (ProductStockNode *)malloc(sizeof(ProductStockNode));
    ProductStockNodeInit(new_node);
    new_node->data = *product_stock;

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
}