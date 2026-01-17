#include <gtest/gtest.h>

extern "C"
{
#include "guards.h"
#include "product_stock.h"
}

namespace
{

class RemoveStockGuard : public testing::Test
{
  protected:
    const ProductStock test_stock_;

    RemoveStockGuard() : test_stock_({.product = NULL, .stock = 100})
    {
    }
};

TEST_F(RemoveStockGuard, StockBiggerThanChange)
{
    const int test_data[] = {0, -1, -20, -99};

    for (auto &&test : test_data)
    {
        EXPECT_EQ(CanRemoveStock(&test_stock_, test), 0) << "Failed for input: " << test;
    }
}

TEST_F(RemoveStockGuard, StockEqualToChange)
{
    EXPECT_EQ(CanRemoveStock(&test_stock_, 100), 0);
}

TEST_F(RemoveStockGuard, StockSmallerThanChange)
{
    const int test_data[] = {-101, -200, -999};

    for (auto &&test : test_data)
    {
        EXPECT_NE(CanRemoveStock(&test_stock_, test), 0) << "Failed for input: " << test;
    }
}

TEST_F(RemoveStockGuard, PositiveChange)
{
    const int test_data[] = {1, 2, 20, 100};

    for (auto &&test : test_data)
    {
        EXPECT_EQ(CanRemoveStock(&test_stock_, test), 0) << "Failed for input: " << test;
    }
}

class WarehouseTakeProductGuardTest : public testing::Test
{
  protected:
    Warehouse test_warehouse;

    WarehouseTakeProductGuardTest()
    {
        WarehouseInit(&test_warehouse);
        strcpy(test_warehouse.id, "WH123");
        strcpy(test_warehouse.name, "TestWarehouse");
        test_warehouse.flammability_max = 5;
        test_warehouse.stock_max = 700;
        test_warehouse.sections.size = 5;
        test_warehouse.sections.data = new WarehouseSection[5];
        test_warehouse.sections.data[0] = {.stock_max = 30, .stock_min_threshold = 10, .category = 4, .subcategory = 3};
        test_warehouse.sections.data[1] = {.stock_max = 50, .stock_min_threshold = 10, .category = 4, .subcategory = 5};
        test_warehouse.sections.data[2] = {
            .stock_max = 400, .stock_min_threshold = 10, .category = 4, .subcategory = SUBCATEGORY_WILDCARD};
        test_warehouse.sections.data[3] = {
            .stock_max = 500, .stock_min_threshold = 10, .category = 5, .subcategory = SUBCATEGORY_WILDCARD};
        test_warehouse.sections.data[4] = {
            .stock_max = 800, .stock_min_threshold = 10, .category = 2, .subcategory = SUBCATEGORY_WILDCARD};
    }
};

TEST_F(WarehouseTakeProductGuardTest, ValidStockChangeNoProductSubcategoryWithNoWarehouseSubcategory)
{
    Product test_product = {
        .id = "AB789", .name = "TestProd", .category = 5, .subcategory = SUBCATEGORY_WILDCARD, .flammability = 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse, &test_product, 100), 0);
}

TEST_F(WarehouseTakeProductGuardTest, ValidStockChangeNoProductSubcategoryWithWarehouseSubcategory)
{
    Product test_product = {
        .id = "AB789", .name = "TestProd", .category = 4, .subcategory = SUBCATEGORY_WILDCARD, .flammability = 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse, &test_product, 100), 0);
}

TEST_F(WarehouseTakeProductGuardTest, ValidStockChangeProductSubcategoryWithWarehouseSubcategory)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 4, .subcategory = 3, .flammability = 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse, &test_product, 20), 0);
}

TEST_F(WarehouseTakeProductGuardTest, StockChangeEqualToWarehouseMax)
{
    Product test_product = {
        .id = "AB789", .name = "TestProd", .category = 2, .subcategory = SUBCATEGORY_WILDCARD, .flammability = 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse, &test_product, 700), 0);
}

TEST_F(WarehouseTakeProductGuardTest, StockChangeHigherThanWarehouseMax)
{
    Product test_product = {
        .id = "AB789", .name = "TestProd", .category = 5, .subcategory = SUBCATEGORY_WILDCARD, .flammability = 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse, &test_product, 701), 0);
}

TEST_F(WarehouseTakeProductGuardTest, FlammabilityEqualToMax)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 4, .subcategory = 3, .flammability = 5};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse, &test_product, 30), 0);
}

TEST_F(WarehouseTakeProductGuardTest, FlammabilityHigherThanMax)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 4, .subcategory = 3, .flammability = 6};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse, &test_product, 30), 0);
}

TEST_F(WarehouseTakeProductGuardTest, StockChangeEqualToSectionMaxProductWithSubcategory)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 4, .subcategory = 3, .flammability = 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse, &test_product, 30), 0);
}

TEST_F(WarehouseTakeProductGuardTest, StockChangeEqualToSectionMaxProductWithCategory)
{
    Product test_product = {
        .id = "AB789", .name = "TestProd", .category = 5, .subcategory = SUBCATEGORY_WILDCARD, .flammability = 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse, &test_product, 500), 0);
}

TEST_F(WarehouseTakeProductGuardTest, StockChangeHigherThanSectionMaxProductWithSubcategory)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 4, .subcategory = 3, .flammability = 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse, &test_product, 31), 0);
}

TEST_F(WarehouseTakeProductGuardTest, StockChangeHigherThanSectionMaxProductWithCategory)
{
    Product test_product = {
        .id = "AB789", .name = "TestProd", .category = 5, .subcategory = SUBCATEGORY_WILDCARD, .flammability = 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse, &test_product, 501), 0);
}

TEST_F(WarehouseTakeProductGuardTest, NonExistentSubcategoryWithOtherSubcategories)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 4, .subcategory = 4, .flammability = 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse, &test_product, 10), 0);
}

TEST_F(WarehouseTakeProductGuardTest, NonExistentSubcategoryWithoutOtherSubcategories)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 5, .subcategory = 3, .flammability = 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse, &test_product, 10), 0);
}

TEST_F(WarehouseTakeProductGuardTest, NonExistentCategoryWithSubcategory)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 3, .subcategory = 4, .flammability = 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse, &test_product, 10), 0);
}

TEST_F(WarehouseTakeProductGuardTest, NonExistentCategoryWithoutSubcategory)
{
    Product test_product = {
        .id = "AB789", .name = "TestProd", .category = 3, .subcategory = SUBCATEGORY_WILDCARD, .flammability = 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse, &test_product, 10), 0);
}

} // namespace