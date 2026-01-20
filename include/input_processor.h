#ifndef WHS_PARSER_H_
#define WHS_PARSER_H_

#include "product.h"
#include "warehouse.h"

void SanitizeRawLine(char *str);
void ParseCommandLine(const char *str, char *command, char *args);
void ParseLineCount(const char *str, int *count);
void ParseUpdateHeader(const char *str, char *warehouse_id);
void ParseUpdateEntry(const char *str, char *product_id, char *operation, int *stock_change);
void ParseInitEntry(const char *str, Product *product);
void ParseJointCategory(const char *str, unsigned int *category, unsigned int *subcategory);
void ParseCreateHeader(const char *str, Warehouse *warehouse);
void ParseCreateEntry(const char *str, WarehouseSection *section);
void ParseTransferHeader(const char *str, char *dst_warehouse_id, char *src_warehouse_id);
void ParseTransferEntry(const char *str, char *product_id, unsigned int *stock_change);
void ParsePrintArgs(const char *str, char *filename, char *flags);

#endif