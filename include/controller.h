#ifndef WAREHOUSE_CONTROLLER_H_
#define WAREHOUSE_CONTROLLER_H_

void HandleCommand(const char *command, const char *args);
void WarehouseInit(const char *filename);
void WarehouseUpdate(const char *filename);
void WarehousePrint(const char *base_filename);
void WarehouseSave();

#endif