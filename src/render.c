#include <stdio.h>
#include <time.h>

#include "common.h"
#include "render.h"

void RenderTxt(FILE *file)
{
    for (int i = 0; i < kProductCount; i++)
    {
        fprintf(file, "%s %s %d\n", kProducts[i].id, kProducts[i].name, kProducts[i].stock);
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
    fprintf(file, "%d:%d %d/%d/%d", time_info->tm_hour, time_info->tm_min, time_info->tm_mday, time_info->tm_mon + 1,
            time_info->tm_year + 1900);
    fprintf(file, "}\n"
                  "\\begin{document}\n"
                  "\\maketitle\n"
                  "\\begin{tabular}{|l|l|l|}\n"
                  "\\hline\n"
                  "ID & Nazwa & Ilość \\\\ \\hline\n");

    for (int i = 0; i < kProductCount; i++)
    {
        fprintf(file, "%s & %s & %d \\\\\n", kProducts[i].id, kProducts[i].name, kProducts[i].stock);
    }

    fprintf(file, "\\hline\n"
                  "\\end{tabular}\n"
                  "\\end{document}\n");
}