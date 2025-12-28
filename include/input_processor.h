#ifndef WHS_PARSER_H_
#define WHS_PARSER_H_

#include "product.h"

void SanitizeRawLine(char *str);
void ParseCommandLine(const char *str, char *command, char *args);
void ParseLineCount(const char *str, unsigned int *count);
void ParseProductLine(const char *str, Product *product);
void ParseJointCategory(const char *str, unsigned int *category, unsigned int *subcategory);

#endif