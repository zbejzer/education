#include <gtest/gtest.h>

#include "warehouse.h"

ProductNode *kProductsHead = NULL;

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}