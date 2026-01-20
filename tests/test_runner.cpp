#include <gtest/gtest.h>

extern "C"
{
#include "product.h"
#include "warehouse.h"
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    ProductListInit(&kProducts);
    WarehouseListInit(&kWarehouses);

    return RUN_ALL_TESTS();
}