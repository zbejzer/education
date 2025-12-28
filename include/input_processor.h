#ifndef WHS_PARSER_H_
#define WHS_PARSER_H_

#include "product.h"
#include "warehouse.h"

void SanitizeRawLine(char *str);
void ParseCommandLine(const char *str, char *command, char *args);
void ParseLineCount(const char *str, int *count);
void ParseProductEntry(const char *str, Product *product);
void ParseJointCategory(const char *str, unsigned int *category, unsigned int *subcategory);
void ParseWarehouseEntry(const char *str, Warehouse *warehouse);
void ParseWarehouseSectionEntry(const char *str, WarehouseSection *section);

#endif