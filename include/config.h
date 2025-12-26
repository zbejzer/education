#ifndef WHS_CONFIG_H_
#define WHS_CONFIG_H_

#include <stdio.h>

#define ID_ALLOCATED_SIZE 6
#define NAME_ALLOCATED_SIZE 128
#define SAVE_FILENAME "store.txt"
#define COMMAND_SIZE_MAX 32
#define LINE_SIZE_MAX 292

#define PRODUCT_ID_SIZE_MAX 5

#define WAREHOUSE_SIZE_MIN 1
#define WAREHOUSE_SIZE_MAX 1000

#define XSTR(s) STR(s)
#define STR(s) #s

#endif