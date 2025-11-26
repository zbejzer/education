#include <stdio.h>

#include "common.h"
#include "render.h"

void RenderTxt(FILE *file)
{
    for (int i = 0; i < product_count; i++)
    {
        fprintf(file, "%s %s %d\n", products[i].id, products[i].name, products[i].stock);
    }
}

void RenderPdf(FILE *file)
{
}