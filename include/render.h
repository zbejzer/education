#ifndef WHS_RENDER_H_
#define WHS_RENDER_H_

#include <stdbool.h>
#include <stdio.h>

void RenderTxt(FILE *file);
void RenderPdf(FILE *file);

extern bool kPdfMode;

#endif