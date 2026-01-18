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

class WarehouseTakeProductGuard : public testing::Test
{
  protected:
    Warehouse test_warehouse_;

    WarehouseTakeProductGuard()
    {
        WarehouseInit(&test_warehouse_);
        strcpy(test_warehouse_.id, "WH123");
        strcpy(test_warehouse_.name, "TestWarehouse");
        test_warehouse_.flammability_max = 5;
        test_warehouse_.stock_max = 700;
        test_warehouse_.sections.size = 5;
        test_warehouse_.sections.data = new WarehouseSection[5];
        test_warehouse_.sections.data[0] = {
            .stock_max = 30, .stock_min_threshold = 10, .category = 4, .subcategory = 3};
        test_warehouse_.sections.data[1] = {
            .stock_max = 50, .stock_min_threshold = 10, .category = 4, .subcategory = 5};
        test_warehouse_.sections.data[2] = {
            .stock_max = 400, .stock_min_threshold = 10, .category = 4, .subcategory = SUBCATEGORY_WILDCARD};
        test_warehouse_.sections.data[3] = {
            .stock_max = 500, .stock_min_threshold = 10, .category = 5, .subcategory = SUBCATEGORY_WILDCARD};
        test_warehouse_.sections.data[4] = {
            .stock_max = 800, .stock_min_threshold = 10, .category = 2, .subcategory = SUBCATEGORY_WILDCARD};
    }

    ~WarehouseTakeProductGuard() override
    {
        delete[] test_warehouse_.sections.data;
    }
};

TEST_F(WarehouseTakeProductGuard, ValidStockChangeNoProductSubcategoryWithNoWarehouseSubcategory)
{
    Product test_product = {
        .id = "AB789", .name = "TestProd", .category = 5, .subcategory = SUBCATEGORY_WILDCARD, .flammability = 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 100), 0);
}

TEST_F(WarehouseTakeProductGuard, ValidStockChangeNoProductSubcategoryWithWarehouseSubcategory)
{
    Product test_product = {
        .id = "AB789", .name = "TestProd", .category = 4, .subcategory = SUBCATEGORY_WILDCARD, .flammability = 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 100), 0);
}

TEST_F(WarehouseTakeProductGuard, ValidStockChangeProductSubcategoryWithWarehouseSubcategory)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 4, .subcategory = 3, .flammability = 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 20), 0);
}

TEST_F(WarehouseTakeProductGuard, StockChangeEqualToWarehouseMax)
{
    Product test_product = {
        .id = "AB789", .name = "TestProd", .category = 2, .subcategory = SUBCATEGORY_WILDCARD, .flammability = 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 700), 0);
}

TEST_F(WarehouseTakeProductGuard, StockChangeHigherThanWarehouseMax)
{
    Product test_product = {
        .id = "AB789", .name = "TestProd", .category = 5, .subcategory = SUBCATEGORY_WILDCARD, .flammability = 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 701), 0);
}

TEST_F(WarehouseTakeProductGuard, FlammabilityEqualToMax)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 4, .subcategory = 3, .flammability = 5};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 30), 0);
}

TEST_F(WarehouseTakeProductGuard, FlammabilityHigherThanMax)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 4, .subcategory = 3, .flammability = 6};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 30), 0);
}

TEST_F(WarehouseTakeProductGuard, StockChangeEqualToSectionMaxProductWithSubcategory)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 4, .subcategory = 3, .flammability = 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 30), 0);
}

TEST_F(WarehouseTakeProductGuard, StockChangeEqualToSectionMaxProductWithCategory)
{
    Product test_product = {
        .id = "AB789", .name = "TestProd", .category = 5, .subcategory = SUBCATEGORY_WILDCARD, .flammability = 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 500), 0);
}

TEST_F(WarehouseTakeProductGuard, StockChangeHigherThanSectionMaxProductWithSubcategory)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 4, .subcategory = 3, .flammability = 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 31), 0);
}

TEST_F(WarehouseTakeProductGuard, StockChangeHigherThanSectionMaxProductWithCategory)
{
    Product test_product = {
        .id = "AB789", .name = "TestProd", .category = 5, .subcategory = SUBCATEGORY_WILDCARD, .flammability = 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 501), 0);
}

TEST_F(WarehouseTakeProductGuard, NonExistentSubcategoryWithOtherSubcategories)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 4, .subcategory = 4, .flammability = 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 10), 0);
}

TEST_F(WarehouseTakeProductGuard, NonExistentSubcategoryWithoutOtherSubcategories)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 5, .subcategory = 3, .flammability = 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 10), 0);
}

TEST_F(WarehouseTakeProductGuard, NonExistentCategoryWithSubcategory)
{
    Product test_product = {.id = "AB789", .name = "TestProd", .category = 3, .subcategory = 4, .flammability = 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 10), 0);
}

TEST_F(WarehouseTakeProductGuard, NonExistentCategoryWithoutSubcategory)
{
    Product test_product = {
        .id = "AB789", .name = "TestProd", .category = 3, .subcategory = SUBCATEGORY_WILDCARD, .flammability = 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 10), 0);
}

} // namespace