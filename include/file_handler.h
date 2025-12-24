#ifndef WHS_FILEHANDLER_H_
#define WHS_FILEHANDLER_H_

#include <stdio.h>

FILE *OpenFile(const char *filename, const char *mode);
int CloseFile(FILE *file);

#endif