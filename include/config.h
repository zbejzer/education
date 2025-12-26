#ifndef WHS_CONFIG_H_
#define WHS_CONFIG_H_

#include <limits.h>
#include <stdio.h>

// Memory limits
#define LINE_BUFFER_LEN_MAX 384
#define COMMAND_LEN_MAX 32
#define PRODUCT_ID_LEN_MAX 5
#define PRODUCT_NAME_LEN_MAX 127
#define WAREHOUSE_ID_LEN_MAX PRODUCT_ID_LEN_MAX
#define WAREHOUSE_NAME_LEN_MAX PRODUCT_NAME_LEN_MAX
#define JOINT_CATEGORY_LEN_MAX 5

// Customary limits
#define PRODUCTS_COUNT_MIN 1
#define PRODUCTS_COUNT_MAX 1000
#define PRODUCT_ID_LEN 5
#define WAREHOUSE_ID_LEN 5
#define CATEGORY_MIN 1
#define CATEGORY_MAX 10
#define SUBCATEGORY_MIN 1
#define SUBCATEGORY_MAX 10

// Conventions
#define SAVE_FILENAME "store.txt"
#define SUBCATEGORY_WILDCARD UINT_MAX

// Macros
#define XSTR(s) STR(s)
#define STR(s) #s

#endif