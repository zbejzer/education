#ifndef WAREHOUSE_COMMAND_PARSER_H_
#define WAREHOUSE_COMMAND_PARSER_H_

void ParseCommand(char *prompt);
void HandleCommand(char *command, char *args);
void WarehouseInit(FILE *input_file);
void WarehouseUpdate(FILE *input_file);
void WarehousePrintTxt(FILE *output_file);
void WarehousePrintPdf(FILE *output_file);
void WarehousePrint(FILE *output_file);
void WarehouseSave();

#endif