#ifndef WHS_STATE_SAVE_H_
#define WHS_STATE_SAVE_H_

#include "product.h"
#include "product_stock.h"
#include "warehouse.h"

int StateSave(ProductList *products, WarehouseList *warehouses);
void StateSaveRender(FILE *stream, ProductList *products, WarehouseList *warehouses);
void StateSaveRenderProduct(FILE *stream, const Product *product);
void StateSaveRenderWarehouse(FILE *stream, const Warehouse *warehouse);
void StateSaveRenderSection(FILE *stream, const WarehouseSection *section);
void StateSaveRenderProductStock(FILE *stream, const ProductStock *stock);

#endif