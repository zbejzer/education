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

    RemoveStockGuard() : test_stock_({NULL, 100})
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
        test_warehouse_.sections.data[0] = {30, 10, 4, 3};
        test_warehouse_.sections.data[1] = {50, 10, 4, 5};
        test_warehouse_.sections.data[2] = {400, 10, 4, SUBCATEGORY_WILDCARD};
        test_warehouse_.sections.data[3] = {500, 10, 5, SUBCATEGORY_WILDCARD};
        test_warehouse_.sections.data[4] = {800, 10, 2, SUBCATEGORY_WILDCARD};
    }

    ~WarehouseTakeProductGuard() override
    {
        delete[] test_warehouse_.sections.data;
    }
};

TEST_F(WarehouseTakeProductGuard, ValidStockChangeNoProductSubcategoryWithNoWarehouseSubcategory)
{
    Product test_product = {"AB789", "TestProd", 5, SUBCATEGORY_WILDCARD, 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 100), 0);
}

TEST_F(WarehouseTakeProductGuard, ValidStockChangeNoProductSubcategoryWithWarehouseSubcategory)
{
    Product test_product = {"AB789", "TestProd", 4, SUBCATEGORY_WILDCARD, 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 100), 0);
}

TEST_F(WarehouseTakeProductGuard, ValidStockChangeProductSubcategoryWithWarehouseSubcategory)
{
    Product test_product = {"AB789", "TestProd", 4, 3, 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 20), 0);
}

TEST_F(WarehouseTakeProductGuard, StockChangeEqualToWarehouseMax)
{
    Product test_product = {"AB789", "TestProd", 2, SUBCATEGORY_WILDCARD, 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 700), 0);
}

TEST_F(WarehouseTakeProductGuard, StockChangeHigherThanWarehouseMax)
{
    Product test_product = {"AB789", "TestProd", 5, SUBCATEGORY_WILDCARD, 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 701), 0);
}

TEST_F(WarehouseTakeProductGuard, FlammabilityEqualToMax)
{
    Product test_product = {"AB789", "TestProd", 4, 3, 5};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 30), 0);
}

TEST_F(WarehouseTakeProductGuard, FlammabilityHigherThanMax)
{
    Product test_product = {"AB789", "TestProd", 4, 3, 6};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 30), 0);
}

TEST_F(WarehouseTakeProductGuard, StockChangeEqualToSectionMaxProductWithSubcategory)
{
    Product test_product = {"AB789", "TestProd", 4, 3, 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 30), 0);
}

TEST_F(WarehouseTakeProductGuard, StockChangeEqualToSectionMaxProductWithCategory)
{
    Product test_product = {"AB789", "TestProd", 5, SUBCATEGORY_WILDCARD, 0};

    EXPECT_EQ(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 500), 0);
}

TEST_F(WarehouseTakeProductGuard, StockChangeHigherThanSectionMaxProductWithSubcategory)
{
    Product test_product = {"AB789", "TestProd", 4, 3, 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 31), 0);
}

TEST_F(WarehouseTakeProductGuard, StockChangeHigherThanSectionMaxProductWithCategory)
{
    Product test_product = {"AB789", "TestProd", 5, SUBCATEGORY_WILDCARD, 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 501), 0);
}

TEST_F(WarehouseTakeProductGuard, NonExistentSubcategoryWithOtherSubcategories)
{
    Product test_product = {"AB789", "TestProd", 4, 4, 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 10), 0);
}

TEST_F(WarehouseTakeProductGuard, NonExistentSubcategoryWithoutOtherSubcategories)
{
    Product test_product = {"AB789", "TestProd", 5, 3, 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 10), 0);
}

TEST_F(WarehouseTakeProductGuard, NonExistentCategoryWithSubcategory)
{
    Product test_product = {"AB789", "TestProd", 3, 4, 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 10), 0);
}

TEST_F(WarehouseTakeProductGuard, NonExistentCategoryWithoutSubcategory)
{
    Product test_product = {"AB789", "TestProd", 3, SUBCATEGORY_WILDCARD, 0};

    EXPECT_NE(CanWarehouseTakeProduct(&test_warehouse_, &test_product, 10), 0);
}

} // namespace