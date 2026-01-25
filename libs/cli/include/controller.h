#ifndef WHS_CONTROLLER_H_
#define WHS_CONTROLLER_H_

#include <stdio.h>

int RouteCommand(const char *command, const char *args);

int HandleCommandInit(void);
int HandleCommandCreate(void);
int HandleCommandUpdate(void);
int HandleCommandTransfer(void);
int HandleCommandPrint(const char *args);

#endif
