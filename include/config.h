#ifndef WHS_CONFIG_H_
#define WHS_CONFIG_H_

#define PRODUCT_ID_SIZE 6 // 5 chars + null character
#define PRODUCT_NAME_SIZE 128
#define SAVE_FILENAME "store.txt"
#define COMMAND_SIZE_MAX 128
#define ARGS_SIZE_MAX 256

#define WAREHOUSE_SIZE_MIN 1
#define WAREHOUSE_SIZE_MAX 1000

#define XSTR(s) STR(s)
#define STR(s) #s

#endif