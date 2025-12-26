#ifndef WHS_CONTROLLER_H_
#define WHS_CONTROLLER_H_

#include <stdio.h>

void ParseCommandLine(const char *command_line, char *command, char *args);
int RouteCommand(const char *command, const char *args);

int HandleCommandInit();
int HandleCommandCreate(const char *args);
int HandleCommandUpdate();
int HandleCommandTransfer(const char *args);
int HandleCommandPrint(const char *args);

#endif