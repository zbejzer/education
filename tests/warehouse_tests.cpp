
#include <gtest/gtest.h>

extern "C"
{
#include "product.h"
#include "shared.h"
#include "warehouse.h"
}

namespace
{

class WarehouseTest : public testing::Test
{
  protected:
    const Product prod1_;
    const Product prod2_;
    const Product prod3_;

    WarehouseTest()
        : prod1_({"AB123", "Product 1", 0}), //
          prod2_({"CD456", "Product 2", 0}), //
          prod3_({"EF789", "Product 3", 0})  //
    {
        kWarehouse = NULL;
    }

    ~WarehouseTest() override
    {
        ClearWarehouse();
    }
};

TEST_F(WarehouseTest, SizeOfEmptyWarehouse)
{
    ASSERT_EQ(kWarehouse, nullptr);
    EXPECT_EQ(GetWarehouseSize(), 0);
}

TEST_F(WarehouseTest, ClearEmptyWarehouse)
{
    ASSERT_EQ(kWarehouse, nullptr);
    EXPECT_EQ(ClearWarehouse(), 0);
    EXPECT_EQ(GetWarehouseSize(), 0);
}

TEST_F(WarehouseTest, AddItemToWarehouse)
{
    EXPECT_EQ(GetWarehouseSize(), 0);
    EXPECT_EQ(AddWarehouseItem(&prod1_), 0);
    EXPECT_EQ(GetWarehouseSize(), 1);
    EXPECT_EQ(AddWarehouseItem(&prod2_), 0);
    EXPECT_EQ(GetWarehouseSize(), 2);
    EXPECT_EQ(AddWarehouseItem(&prod3_), 0);
    EXPECT_EQ(GetWarehouseSize(), 3);
}

TEST_F(WarehouseTest, ClearNonEmptyWarehouse)
{
    EXPECT_EQ(AddWarehouseItem(&prod1_), 0);
    EXPECT_EQ(ClearWarehouse(), 0);
    EXPECT_EQ(GetWarehouseSize(), 0);
}

TEST_F(WarehouseTest, RetrieveNonExistentItem)
{
    ASSERT_EQ(kWarehouse, nullptr);
    Product *retrieved_product = GetWarehouseItemById("ZZ999");
    EXPECT_EQ(retrieved_product, nullptr);
}

TEST_F(WarehouseTest, RetrieveExistingItem)
{
    ASSERT_EQ(AddWarehouseItem(&prod1_), 0);
    Product *retrieved_product = GetWarehouseItemById(prod1_.id);
    ASSERT_NE(retrieved_product, nullptr);

    EXPECT_STREQ(retrieved_product->id, prod1_.id);
    EXPECT_STREQ(retrieved_product->name, prod1_.name);
    EXPECT_EQ(retrieved_product->stock, prod1_.stock);
}

TEST_F(WarehouseTest, DifferentiateItems)
{
    ASSERT_EQ(AddWarehouseItem(&prod1_), 0);
    ASSERT_EQ(AddWarehouseItem(&prod2_), 0);
    ASSERT_EQ(AddWarehouseItem(&prod3_), 0);

    Product *retrieved_product1 = GetWarehouseItemById(prod1_.id);
    ASSERT_NE(retrieved_product1, nullptr);
    EXPECT_STREQ(retrieved_product1->id, prod1_.id);
    EXPECT_STREQ(retrieved_product1->name, prod1_.name);
    EXPECT_EQ(retrieved_product1->stock, prod1_.stock);

    Product *retrieved_product2 = GetWarehouseItemById(prod2_.id);
    ASSERT_NE(retrieved_product2, nullptr);
    EXPECT_STREQ(retrieved_product2->id, prod2_.id);
    EXPECT_STREQ(retrieved_product2->name, prod2_.name);
    EXPECT_EQ(retrieved_product2->stock, prod2_.stock);
    EXPECT_NE(retrieved_product1, retrieved_product2);

    Product *retrieved_product3 = GetWarehouseItemById(prod3_.id);
    ASSERT_NE(retrieved_product3, nullptr);
    EXPECT_STREQ(retrieved_product3->id, prod3_.id);
    EXPECT_STREQ(retrieved_product3->name, prod3_.name);
    EXPECT_EQ(retrieved_product3->stock, prod3_.stock);
    EXPECT_NE(retrieved_product1, retrieved_product3);
    EXPECT_NE(retrieved_product2, retrieved_product3);
}

TEST_F(WarehouseTest, AddItemStock)
{
    ASSERT_EQ(AddWarehouseItem(&prod1_), 0);
    Product *retrieved_product = GetWarehouseItemById(prod1_.id);
    ASSERT_NE(retrieved_product, nullptr);

    EXPECT_EQ(UpdateWarehouseItem(prod1_.id, 10), 0);
    EXPECT_EQ(retrieved_product->stock, 10);
}

TEST_F(WarehouseTest, AddItemStockMultipleTimes)
{
    ASSERT_EQ(AddWarehouseItem(&prod1_), 0);
    Product *retrieved_product = GetWarehouseItemById(prod1_.id);
    ASSERT_NE(retrieved_product, nullptr);

    EXPECT_EQ(UpdateWarehouseItem(prod1_.id, 10), 0);
    EXPECT_EQ(retrieved_product->stock, 10);
    EXPECT_EQ(UpdateWarehouseItem(prod1_.id, 15), 0);
    EXPECT_EQ(retrieved_product->stock, 25);
    EXPECT_EQ(UpdateWarehouseItem(prod1_.id, 5), 0);
    EXPECT_EQ(retrieved_product->stock, 30);
}

TEST_F(WarehouseTest, RemoveItemStock)
{
    EXPECT_EQ(AddWarehouseItem(&prod1_), 0);
    Product *retrieved_product = GetWarehouseItemById(prod1_.id);
    ASSERT_NE(retrieved_product, nullptr);

    EXPECT_EQ(UpdateWarehouseItem(prod1_.id, 20), 0);
    EXPECT_EQ(retrieved_product->stock, 20);

    EXPECT_EQ(UpdateWarehouseItem(prod1_.id, -5), 0);
    EXPECT_EQ(retrieved_product->stock, 15);
}

TEST_F(WarehouseTest, RemoveItemStockBelowZero)
{
    EXPECT_EQ(AddWarehouseItem(&prod1_), 0);
    Product *retrieved_product = GetWarehouseItemById(prod1_.id);
    ASSERT_NE(retrieved_product, nullptr);

    EXPECT_EQ(UpdateWarehouseItem(prod1_.id, 5), 0);
    EXPECT_EQ(retrieved_product->stock, 5);

    EXPECT_NE(UpdateWarehouseItem(prod1_.id, -10), 0);
    EXPECT_EQ(retrieved_product->stock, 5);
}

} // namespace