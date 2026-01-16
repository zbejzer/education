#include <stdbool.h>

#include "product.h"
#include "warehouse.h"

int ValidateProductsCount(const int count);
int ValidateProductId(const char *str);
int ValidateProductName(const char *str);

int ValidateWarehouseSectionCount(const int count);

int ValidateWarehouseId(const char *str);
int ValidateWarehouseName(const char *str);

int ValidatePrintFilename(const char *str);
int ValidateGenericFilename(const char *str);