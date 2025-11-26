#ifndef WAREHOUSE_PRODUCT_H_
#define WAREHOUSE_PRODUCT_H_

#define PRODUCT_ID_SIZE 6 // 5 chars + null character
#define PRODUCT_NAME_SIZE 128
#define STR_PRODUCT_NAME_SIZE "128"

typedef struct Product
{
    char id[PRODUCT_ID_SIZE];
    char name[PRODUCT_NAME_SIZE];
    int stock;
} Product;

#endif