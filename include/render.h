#ifndef WHS_RENDER_H_
#define WHS_RENDER_H_

#include <stdbool.h>
#include <stdio.h>

#include "product.h"
#include "product_stock.h"
#include "warehouse.h"
#include "warehouse_section.h"

void RenderTxt(FILE *file);
void RenderTxtProduct(FILE *file, const Product *product);
void RenderTxtWarehouse(FILE *file, const Warehouse *warehouse);
void RenderTxtSectionList(FILE *file, const WarehouseSectionList *list);
void RenderTxtStockList(FILE *file, const ProductStockList *list);

void RenderPdf(FILE *file);
void RenderJointCategory(char *buffer, unsigned int category, unsigned int subcategory);

extern bool kPdfMode;

#endif