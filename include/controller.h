#ifndef WHS_CONTROLLER_H_
#define WHS_CONTROLLER_H_

#include <stdio.h>

void ParseCommandLine(const char *command_line, char *command, char *args);
void RouteCommand(const char *command, const char *args);
FILE *SelectInputStream(const char *command, const char *args);

void HandleCommandInit(const char *args);
void HandleCommandCreate(const char *args);
void HandleCommandUpdate(const char *args);
void HandleCommandTransfer(const char *args);
void HandleCommandPrint(const char *args);

#endif