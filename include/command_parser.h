#ifndef WAREHOUSE_COMMAND_PARSER_H_
#define WAREHOUSE_COMMAND_PARSER_H_

void ParseCommand(char *prompt);
void HandleCommand(char *command, char *args);
void WarehouseInit(const char *filename);
void WarehouseUpdate(const char *filename);
void WarehousePrint(const char *base_filename);
void WarehouseSave();

#endif