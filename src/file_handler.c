#include <stdlib.h>

#include "file_handler.h"

FILE *OpenFile(const char *filename, const char *mode)
{
    FILE *file = fopen(filename, mode);

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file %s with mode %s\n", filename, mode);
    }

    return file;
}

int CloseFile(FILE *file)
{
    if (fclose(file) == EOF)
    {
        fprintf(stderr, "Could not close file properly\n");
        return 1;
    }

    return 0;
}