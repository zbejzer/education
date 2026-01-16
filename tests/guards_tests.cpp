#include <gtest/gtest.h>

extern "C"
{
#include "guards.h"
#include "product_stock.h"
}

namespace
{

TEST(RemoveStockGuard, StockBiggerThanChange)
{
    const ProductStock test_stock = {.product = NULL, .stock = 100};
    const int test_data[] = {0, -1, -20, -99};

    for (auto &&test : test_data)
    {
        EXPECT_EQ(CanRemoveStock(&test_stock, test), 0) << "Failed for input: " << test;
    }
}

TEST(RemoveStockGuard, StockEqualToChange)
{
    const ProductStock test_stock = {.product = NULL, .stock = 100};

    EXPECT_EQ(CanRemoveStock(&test_stock, 100), 0);
}

TEST(RemoveStockGuard, StockSmallerThanChange)
{
    const ProductStock test_stock = {.product = NULL, .stock = 100};

    const int test_data[] = {-101, -200, -999};

    for (auto &&test : test_data)
    {
        EXPECT_NE(CanRemoveStock(&test_stock, test), 0) << "Failed for input: " << test;
    }
}

TEST(RemoveStockGuard, PositiveChange)
{
    const ProductStock test_stock = {.product = NULL, .stock = 100};

    const int test_data[] = {1, 2, 20, 100};

    for (auto &&test : test_data)
    {
        EXPECT_EQ(CanRemoveStock(&test_stock, test), 0) << "Failed for input: " << test;
    }
}

} // namespace