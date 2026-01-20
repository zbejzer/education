#ifndef WHS_RENDER_H_
#define WHS_RENDER_H_

#include <stdbool.h>
#include <stdio.h>

#include "product.h"
#include "product_stock.h"
#include "warehouse.h"
#include "warehouse_section.h"

void RenderTxt(FILE *stream, WarehouseList *warehouses);
void RenderTxtWarehouse(FILE *stream, const Warehouse *warehouse);
void RenderTxtProductStock(FILE *stream, const ProductStock *stock);

void RenderPdf(FILE *stream, WarehouseList *warehouses);
void RenderPdfWarehouse(FILE *stream, const Warehouse *warehouse);
void RenderPdfProductStock(FILE *stream, const ProductStock *stock);

void RenderJointCategory(char *buffer, unsigned int category, unsigned int subcategory);

extern bool kPdfMode;

#endif