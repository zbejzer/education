#ifndef WHS_RENDER_H_
#define WHS_RENDER_H_

#include <stdbool.h>
#include <stdio.h>

void RenderTxt(FILE *file);
void RenderPdf(FILE *file);
void RenderJointCategory(char *buffer, unsigned int category, unsigned int subcategory);

extern bool kPdfMode;

#endif