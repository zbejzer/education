#include <stdbool.h>

#include "product.h"
#include "warehouse.h"

int ValidateProductsCount(const int count);
int ValidateProductListClear(const ProductList *list);
int ValidateProductId(const char *str);
int ValidateProductName(const char *str);

int ValidateWarehouseSectionCount(const int count);
int ValidateWarehouseListClear(const WarehouseList *list);

int ValidateWarehouseId(const char *str);
int ValidateWarehouseName(const char *str);

int ValidateFilename(const char *str);