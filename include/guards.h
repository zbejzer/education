#ifndef WHS_GUARDS_H_
#define WHS_GUARDS_H_

#include "product_stock.h"
#include "warehouse.h"
#include "warehouse_section.h"

int CanRemoveStock(const ProductStock *product_stock, const int stock_change);
int CanWarehouseTakeProduct(const Warehouse *warehouse, const Product *product, const int stock_change);

#endif