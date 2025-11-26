#include "product.h"

#include <stdlib.h>
#include <string.h>

Product ProductCreate(char *id_, char *name_)
{
    Product new_product;

    strcpy(new_product.id, id_);
    new_product.name = malloc(strlen(name_) * sizeof(char));
    new_product.stock = 0;

    return new_product;
}

void ProductDelete(Product *product_)
{
    free(product_->name);
}
