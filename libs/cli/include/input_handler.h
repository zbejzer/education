#ifndef WHS_FILEHANDLER_H_
#define WHS_FILEHANDLER_H_

#include <stdio.h>

int InputStreamDetect(const char *filename, const char *mode);
int InputStreamSwitch(FILE *stream);
int InputStreamOpen(const char *filename, const char *mode);

extern FILE *kInputStream;

#endif
