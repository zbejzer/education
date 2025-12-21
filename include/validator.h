#include <stdbool.h>

#include "warehouse.h"

int ValidateWarehouseSize(const int products);
int ValidateWarehouseInitialized(const WarehouseNode *warehouse);
int ValidateProductId(const char *str);
int ValidateProductName(const char *str);