#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"

int AddProductToRegistry(const Product *product)
{
    // ProductNode *new_node = malloc(sizeof(ProductNode));
    // if (new_node == NULL)
    // {
    //     fprintf(stderr, "Memory allocation for new ProductNode failed!\n");
    //     return 1;
    // }

    // new_node->product = product;
    // new_node->next = NULL;

    // ProductNode **last_node_ptr = GetProductsTailSuccessorPtr();

    // *last_node_ptr = new_node;

    return 0;
}

Product *GetProductById(const char *product_id)
{
    // ProductNode *node = kProductsRegistry;
    // while (node != NULL)
    // {
    //     if (strcmp(node->product->id, product_id) == 0)
    //     {
    //         return node->product;
    //     }
    //     node = node->next;
    // }

    // fprintf(stderr, "Product with ID %s does not exist!\n", product_id);
    return NULL;
}

int UpdateProduct(Product *product, const int stock_change)
{
    // if (stock_change < 0 && product->stock < (unsigned int)(-stock_change))
    // {
    //     fprintf(stderr, "Insufficient stock for product ID %s to remove %d units!\n", product->id, -stock_change);
    //     return 1;
    // }

    // product->stock += stock_change;
    return 0;
}

size_t GetRegisteredProductCount()
{
    size_t size = 0;
    // ProductNode *node = kProductsRegistry;

    // while (node != NULL)
    // {
    //     size++;
    //     node = node->next;
    // }

    return size;
}

int ClearRegisteredProducts()
{
    // ProductNode *node = kProductsRegistry;
    // kProductsRegistry = NULL;
    // while (node != NULL)
    // {
    //     ProductNode *temp = node;
    //     node = node->next;
    //     free(temp->product);
    //     free(temp);
    // }

    return 0;
}

Product *kProductsRegistry;