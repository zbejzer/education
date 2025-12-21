#ifndef WHS_CONTROLLER_H_
#define WHS_CONTROLLER_H_

void HandleCommand(const char *command, const char *args);
void CommandInitialize(const char *filename);
void CommandUpdate(const char *filename);
void CommandPrint(const char *base_filename);

#endif