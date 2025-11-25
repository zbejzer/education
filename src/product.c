#include "product.h"

#include <stdlib.h>
#include <string.h>

Product ProductCreate(char *id_, char *name_)
{
    Product new_product;

    new_product.id = malloc(strlen(id_) * sizeof(char));
    new_product.id = malloc(strlen(name_) * sizeof(char));

    return new_product;
}

void ProductUpdateName(Product *product_)
{
}
