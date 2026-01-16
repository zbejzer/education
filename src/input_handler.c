#include <stdlib.h>

#include "input_handler.h"
#include "validator.h"

int InputStreamDetect(const char *filename, const char *mode)
{
    if (!ValidateGenericFilename(filename))
    {
        return InputStreamOpen(filename, mode);
    }

    return InputStreamSwitch(stdin);
}

int InputStreamSwitch(FILE *stream)
{
    if (kInputStream == stdin || kInputStream == NULL)
    {
        kInputStream = stream;
        return 0;
    }

    if (fclose(kInputStream))
    {
        fprintf(stderr, "Could not close stream properly\n");
        return 1;
    }

    kInputStream = stream;
    return 0;
}

int InputStreamOpen(const char *filename, const char *mode)
{
    FILE *stream = fopen(filename, mode);
    if (stream == NULL)
    {
        fprintf(stderr, "Could not open file %s with mode %s\n", filename, mode);
        return 1;
    }
    return InputStreamSwitch(stream);
}

FILE *kInputStream;