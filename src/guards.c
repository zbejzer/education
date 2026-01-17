#include "guards.h"
#include "config.h"
#include "product.h"
#include "render.h"
#include "warehouse.h"
#include "warehouse_section.h"

int CanRemoveStock(const ProductStock *product_stock, const int stock_change)
{
    if ((int)product_stock->stock + stock_change < 0)
    {
        fprintf(stderr, "Insufficient stock for product ID %s to remove %d units!\n", product_stock->product->id,
                -stock_change);
        return 1;
    }

    return 0;
}

int CanWarehouseTakeProduct(const Warehouse *warehouse, const Product *product, const int stock_change)
{
    WarehouseSection *warehouse_section = NULL;
    WarehouseSection *warehouse_subsection = NULL;
    unsigned int warehouse_section_stock = 0;
    unsigned int warehouse_subsection_stock = 0;

    char category_string[JOINT_CATEGORY_LEN_MAX] = "";

    if (product->flammability > warehouse->flammability_max)
    {
        fprintf(stderr, "Product with ID %s exceeds warehouse max flammability(%d)!\n", product->id,
                warehouse->flammability_max);
        return 1;
    }

    if (stock_change + (int)ProductStockListGetTotalStock(&warehouse->products) > (int)warehouse->stock_max)
    {
        fprintf(stderr, "Stock change by %d exceeds total warehouse capacity(%d)!\n", stock_change,
                warehouse->stock_max);
        return 1;
    }

    warehouse_section = WarehouseSectionListGetSection(&warehouse->sections, product->category);

    if (warehouse_section == NULL)
    {
        fprintf(stderr, "No suitable category(%d) for product with ID %s!\n", product->category, product->id);
        return 1;
    }

    warehouse_section_stock =
        ProductStockListGetCategoryStock(&warehouse->products, product->category, SUBCATEGORY_WILDCARD);

    if (stock_change + (int)warehouse_section_stock > (int)warehouse_section->stock_max)
    {
        fprintf(stderr, "Stock change by %d exceeds category %d limit(%d)!\n", stock_change, product->category,
                warehouse_section->stock_max);
        return 1;
    }

    if (product->subcategory != SUBCATEGORY_WILDCARD)
    {
        warehouse_subsection =
            WarehouseSectionListGetSubsection(&warehouse->sections, product->category, product->subcategory);

        if (warehouse_subsection == NULL)
        {
            RenderJointCategory(category_string, product->category, product->subcategory);
            fprintf(stderr, "No suitable subcategory(%s) for product with ID %s!\n", category_string, product->id);
            return 1;
        }

        warehouse_subsection_stock =
            ProductStockListGetCategoryStock(&warehouse->products, product->category, product->subcategory);

        if (stock_change + (int)warehouse_subsection_stock > (int)warehouse_subsection->stock_max)
        {
            fprintf(stderr, "Stock change by %d exceeds subcategory %d.%d limit(%d)!\n", stock_change,
                    product->category, product->subcategory, warehouse_subsection->stock_max);
            return 1;
        }
    }

    return 0;
}
