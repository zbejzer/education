#include <stdio.h>
#include <time.h>

#include "product.h"
#include "render.h"

void RenderTxt(FILE *file)
{
    for (size_t i = 0; i < kProducts.size; i++)
    {
        // fprintf(file, "%s %s %d\n", node->product->id, node->product->name, node->product->stock);
    }
}

void RenderPdf(FILE *file)
{
    time_t raw_time = time(NULL);
    struct tm *time_info = localtime(&raw_time);

    fprintf(file, "\\documentclass{article}\n"
                  "\\usepackage{polski}\n"
                  "\\title{Stan Magazynu}\n"
                  "\\date{");
    fprintf(file, "%.2d:%.2d %.2d/%.2d/%.4d", time_info->tm_hour, time_info->tm_min, time_info->tm_mday,
            time_info->tm_mon + 1, time_info->tm_year + 1900);
    fprintf(file, "}\n"
                  "\\begin{document}\n"
                  "\\maketitle\n"
                  "\\begin{tabular}{|l|l|l|}\n"
                  "\\hline\n"
                  "ID & Nazwa & Ilość \\\\ \\hline\n");

    for (size_t i = 0; i < kProducts.size; i++)
    {
        // fprintf(file, "%s & %s & %d \\\\\n", node->product->id, node->product->name, node->product->stock);
    }

    fprintf(file, "\\hline\n"
                  "\\end{tabular}\n"
                  "\\end{document}\n");
}

bool kPdfMode = false;