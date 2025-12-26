#ifndef WHS_PARSER_H_
#define WHS_PARSER_H_

#include "product.h"

void ParseCommandLine(const char *command_line, char *command, char *args);
void ParseProductLine(const char *product_line, Product *product);
void ParseJointCategory(const char *joint_category, unsigned int *category, unsigned int *subcategory);

#endif