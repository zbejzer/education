#include <stdio.h>
#include <time.h>

#include "product.h"
#include "render.h"
#include "warehouse.h"

void RenderTxt(FILE *stream, WarehouseList *warehouses)
{
    WarehouseNode *warehouse_node = warehouses->front;

    while (warehouse_node != NULL)
    {
        RenderTxtWarehouse(stream, &warehouse_node->data);
        warehouse_node = warehouse_node->next;
    }
}

void RenderTxtWarehouse(FILE *stream, const Warehouse *warehouse)
{
    ProductStockNode *stock_node = warehouse->products.front;

    fprintf(stream, "%s\t%s\n", warehouse->id, warehouse->name);
    while (stock_node != NULL)
    {
        if (stock_node->data.stock > 0)
        {
            RenderTxtProductStock(stream, &stock_node->data);
        }

        stock_node = stock_node->next;
    }
}

void RenderTxtProductStock(FILE *stream, const ProductStock *stock)
{
    fprintf(stream, "%s ", stock->product->id);
    fprintf(stream, "%u ", stock->stock);
    fprintf(stream, "%s ", stock->product->name);
    fprintf(stream, "%u", stock->product->category);
    if (stock->product->subcategory != SUBCATEGORY_WILDCARD)
    {
        fprintf(stream, ".%u", stock->product->subcategory);
    }
    fprintf(stream, " %u\n", stock->product->flammability);
}

void RenderPdf(FILE *stream)
{
    time_t raw_time = time(NULL);
    struct tm *time_info = localtime(&raw_time);

    fprintf(stream, "\\documentclass{article}\n"
                    "\\usepackage{polski}\n"
                    "\\title{Stan Magazynu}\n"
                    "\\date{");
    fprintf(stream, "%.2d:%.2d %.2d/%.2d/%.4d", time_info->tm_hour, time_info->tm_min, time_info->tm_mday,
            time_info->tm_mon + 1, time_info->tm_year + 1900);
    fprintf(stream, "}\n"
                    "\\begin{document}\n"
                    "\\maketitle\n"
                    "\\begin{tabular}{|l|l|l|}\n"
                    "\\hline\n"
                    "ID & Nazwa & Ilość \\\\ \\hline\n");

    for (size_t i = 0; i < kProducts.size; i++)
    {
        // fprintf(stream, "%s & %s & %d \\\\\n", node->product->id, node->product->name, node->product->stock);
    }

    fprintf(stream, "\\hline\n"
                    "\\end{tabular}\n"
                    "\\end{document}\n");
}

void RenderJointCategory(char *buffer, unsigned int category, unsigned int subcategory)
{
    if (subcategory == SUBCATEGORY_WILDCARD)
    {
        sprintf(buffer, "%d", category);
    }
    else
    {
        sprintf(buffer, "%d.%d", category, subcategory);
    }
}

bool kPdfMode = false;