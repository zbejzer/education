#ifndef WHS_PRODUCT_H_
#define WHS_PRODUCT_H_

#include <stdbool.h>

#include "config.h"

typedef struct Product
{
    char id[PRODUCT_ID_SIZE];
    char name[PRODUCT_NAME_SIZE];
    unsigned int stock;
} Product;

#endif