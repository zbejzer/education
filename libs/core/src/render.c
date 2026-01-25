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

    fprintf(stream, "%s\n", warehouse->id);
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

void RenderPdf(FILE *stream, WarehouseList *warehouses)
{
    WarehouseNode *warehouse_node = warehouses->front;
    time_t raw_time = time(NULL);
    struct tm *time_info = localtime(&raw_time);

    fprintf(stream, "\\documentclass{article}\n"
                    "\\usepackage{polski}\n"
                    "\\title{Stan Magazynu}\n");
    fprintf(stream,
            "\\date{"
            "%.2d:%.2d %.2d/%.2d/%.4d"
            "}",
            time_info->tm_hour, time_info->tm_min, time_info->tm_mday, time_info->tm_mon + 1,
            time_info->tm_year + 1900);

    fprintf(stream, "\\begin{document}\n"
                    "\\maketitle\n");

    while (warehouse_node != NULL)
    {
        RenderPdfWarehouse(stream, &warehouse_node->data);
        warehouse_node = warehouse_node->next;
    }

    fprintf(stream, "\\end{document}\n");
}

void RenderPdfWarehouse(FILE *stream, const Warehouse *warehouse)
{
    ProductStockNode *stock_node = warehouse->products.front;

    fprintf(stream, "\\section{%s}", warehouse->id);

    if (ProductStockListGetTotalStock(&warehouse->products) > 0)
    {
        fprintf(stream, "\\begin{tabular}{|l|l|l|}\n"
                        "\\hline\n"
                        "ID & Ilość & Nazwa \\\\\n"
                        "\\hline\n");

        while (stock_node != NULL)
        {
            if (stock_node->data.stock > 0)
            {
                RenderPdfProductStock(stream, &stock_node->data);
            }

            stock_node = stock_node->next;
        }

        fprintf(stream, "\\hline\n"
                        "\\end{tabular}\n");
    }
}

void RenderPdfProductStock(FILE *stream, const ProductStock *stock)
{
    fprintf(stream, "%s & %u & %s \\\\", stock->product->id, stock->stock, stock->product->name);
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
