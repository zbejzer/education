#ifndef WHS_CONTROLLER_H_
#define WHS_CONTROLLER_H_

#include <stdio.h>

int RouteCommand(const char *command, const char *args);

int HandleCommandInit();
int HandleCommandCreate();
int HandleCommandUpdate();
int HandleCommandTransfer();
int HandleCommandPrint(const char *args);

#endif