#ifndef WHS_GUARDS_H_
#define WHS_GUARDS_H_

#include "product_stock.h"
#include "warehouse.h"
#include "warehouse_section.h"

int CanRemoveStock(const ProductStock *product_stock, const int stock_change);
int CanWarehouseTakeProduct(const Warehouse *warehouse, const Product *product, const int stock_change);
int CanSectionCapacityFitStockThreshold(const WarehouseSection *section);
int CanWarehouseFitSectionCapacity(const WarehouseSection *section, const Warehouse *warehouse);
int CanWarehouseFitTotalStockThreshold(const Warehouse *warehouse);
int CanAllSectionsFitSubsections(const WarehouseSectionList *list);
int CanSectionFitAllSubsections(const WarehouseSectionList *list, const unsigned int category);
int CanAllSectionsFitSubsectionsTotalStockThreshold(const WarehouseSectionList *list);

#endif
