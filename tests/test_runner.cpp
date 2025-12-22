#include <gtest/gtest.h>

#include "warehouse.h"

WarehouseNode *kWarehouse = NULL;

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}