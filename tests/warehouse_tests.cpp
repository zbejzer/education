
#include <gtest/gtest.h>
#include <string.h>

extern "C"
{
#include "warehouse.h"
}

namespace
{

class WarehouseListTest : public testing::Test
{
  protected:
    WarehouseNode *warehouse_node_1_;
    WarehouseNode *warehouse_node_2_;
    WarehouseNode *warehouse_node_3_;

    WarehouseListTest()
        : warehouse_node_1_((WarehouseNode *)malloc(sizeof(WarehouseNode))), //
          warehouse_node_2_((WarehouseNode *)malloc(sizeof(WarehouseNode))), //
          warehouse_node_3_((WarehouseNode *)malloc(sizeof(WarehouseNode)))  //
    {
        WarehouseListInit(&kWarehouses);
        WarehouseNodeInit(warehouse_node_1_);
        WarehouseNodeInit(warehouse_node_2_);
        WarehouseNodeInit(warehouse_node_3_);
        strcpy(warehouse_node_1_->data.id, "AB123");
        strcpy(warehouse_node_2_->data.id, "CD456");
        strcpy(warehouse_node_3_->data.id, "EF789");
    }

    ~WarehouseListTest() override
    {
        free(warehouse_node_1_);
        free(warehouse_node_2_);
        free(warehouse_node_3_);
        WarehouseListInit(&kWarehouses);
    }
};

TEST_F(WarehouseListTest, ClearNonEmpty)
{
    kWarehouses.front = warehouse_node_1_;
    warehouse_node_1_->next = warehouse_node_2_;
    warehouse_node_2_->next = warehouse_node_3_;
    kWarehouses.back = warehouse_node_3_;
    kWarehouses.size = 3;

    warehouse_node_1_ = nullptr;
    warehouse_node_2_ = nullptr;
    warehouse_node_3_ = nullptr;

    WarehouseListClear();

    EXPECT_EQ(kWarehouses.size, 0);
    EXPECT_EQ(kWarehouses.front, nullptr);
    EXPECT_EQ(kWarehouses.back, nullptr);
}

TEST_F(WarehouseListTest, ClearEmpty)
{
    ASSERT_EQ(kWarehouses.front, nullptr);
    ASSERT_EQ(kWarehouses.back, nullptr);
    ASSERT_EQ(kWarehouses.size, 0);
    EXPECT_EQ(WarehouseListClear(), 0);
    EXPECT_EQ(kWarehouses.front, nullptr);
    EXPECT_EQ(kWarehouses.back, nullptr);
    EXPECT_EQ(kWarehouses.size, 0);
}

TEST_F(WarehouseListTest, Push)
{
    EXPECT_EQ(WarehouseListPush(warehouse_node_1_), 0);
    EXPECT_EQ(kWarehouses.front, warehouse_node_1_);
    EXPECT_EQ(kWarehouses.back, warehouse_node_1_);
    EXPECT_EQ(kWarehouses.size, 1);
    EXPECT_EQ(warehouse_node_1_->next, nullptr);

    EXPECT_EQ(WarehouseListPush(warehouse_node_2_), 0);
    EXPECT_EQ(kWarehouses.front, warehouse_node_1_);
    EXPECT_EQ(kWarehouses.back, warehouse_node_2_);
    EXPECT_EQ(kWarehouses.size, 2);
    EXPECT_EQ(warehouse_node_1_->next, warehouse_node_2_);
    EXPECT_EQ(warehouse_node_2_->next, nullptr);

    EXPECT_EQ(WarehouseListPush(warehouse_node_3_), 0);
    EXPECT_EQ(kWarehouses.front, warehouse_node_1_);
    EXPECT_EQ(kWarehouses.back, warehouse_node_3_);
    EXPECT_EQ(kWarehouses.size, 3);
    EXPECT_EQ(warehouse_node_1_->next, warehouse_node_2_);
    EXPECT_EQ(warehouse_node_2_->next, warehouse_node_3_);
    EXPECT_EQ(warehouse_node_3_->next, nullptr);
}

// TEST_F(WarehouseListTest, ProductAddToRegistry)
// {
//     EXPECT_EQ(ProductGetCount(), 0);
//     EXPECT_EQ(ProductAddToRegistry(&prod1_), 0);
//     EXPECT_EQ(ProductGetCount(), 1);
//     EXPECT_EQ(ProductAddToRegistry(&prod2_), 0);
//     EXPECT_EQ(ProductGetCount(), 2);
//     EXPECT_EQ(ProductAddToRegistry(&prod3_), 0);
//     EXPECT_EQ(ProductGetCount(), 3);
// }

// TEST_F(WarehouseListTest, ClearNonEmptyWarehouse)
// {
//     EXPECT_EQ(ProductAddToRegistry(&prod1_), 0);
//     EXPECT_EQ(ProductClearAll(), 0);
//     EXPECT_EQ(ProductGetCount(), 0);
// }

// TEST_F(WarehouseListTest, RetrieveNonExistentItem)
// {
//     ASSERT_EQ(kProductsHead, nullptr);
//     Product *retrieved_product = ProductGetById("ZZ999");
//     EXPECT_EQ(retrieved_product, nullptr);
// }

// TEST_F(WarehouseListTest, RetrieveExistingItem)
// {
//     ASSERT_EQ(ProductAddToRegistry(&prod1_), 0);
//     Product *retrieved_product = ProductGetById(prod1_.id);
//     ASSERT_NE(retrieved_product, nullptr);

//     EXPECT_STREQ(retrieved_product->id, prod1_.id);
//     EXPECT_STREQ(retrieved_product->name, prod1_.name);
//     EXPECT_EQ(retrieved_product->stock, prod1_.stock);
// }

// TEST_F(WarehouseListTest, DifferentiateItems)
// {
//     ASSERT_EQ(ProductAddToRegistry(&prod1_), 0);
//     ASSERT_EQ(ProductAddToRegistry(&prod2_), 0);
//     ASSERT_EQ(ProductAddToRegistry(&prod3_), 0);

//     Product *retrieved_product1 = ProductGetById(prod1_.id);
//     ASSERT_NE(retrieved_product1, nullptr);
//     EXPECT_STREQ(retrieved_product1->id, prod1_.id);
//     EXPECT_STREQ(retrieved_product1->name, prod1_.name);
//     EXPECT_EQ(retrieved_product1->stock, prod1_.stock);

//     Product *retrieved_product2 = ProductGetById(prod2_.id);
//     ASSERT_NE(retrieved_product2, nullptr);
//     EXPECT_STREQ(retrieved_product2->id, prod2_.id);
//     EXPECT_STREQ(retrieved_product2->name, prod2_.name);
//     EXPECT_EQ(retrieved_product2->stock, prod2_.stock);
//     EXPECT_NE(retrieved_product1, retrieved_product2);

//     Product *retrieved_product3 = ProductGetById(prod3_.id);
//     ASSERT_NE(retrieved_product3, nullptr);
//     EXPECT_STREQ(retrieved_product3->id, prod3_.id);
//     EXPECT_STREQ(retrieved_product3->name, prod3_.name);
//     EXPECT_EQ(retrieved_product3->stock, prod3_.stock);
//     EXPECT_NE(retrieved_product1, retrieved_product3);
//     EXPECT_NE(retrieved_product2, retrieved_product3);
// }

// TEST_F(WarehouseListTest, AddItemStock)
// {
//     ASSERT_EQ(ProductAddToRegistry(&prod1_), 0);
//     Product *retrieved_product = ProductGetById(prod1_.id);
//     ASSERT_NE(retrieved_product, nullptr);

//     EXPECT_EQ(UpdateWarehouseItem(prod1_.id, 10), 0);
//     EXPECT_EQ(retrieved_product->stock, 10);
// }

// TEST_F(WarehouseListTest, AddItemStockMultipleTimes)
// {
//     ASSERT_EQ(ProductAddToRegistry(&prod1_), 0);
//     Product *retrieved_product = ProductGetById(prod1_.id);
//     ASSERT_NE(retrieved_product, nullptr);

//     EXPECT_EQ(UpdateWarehouseItem(prod1_.id, 10), 0);
//     EXPECT_EQ(retrieved_product->stock, 10);
//     EXPECT_EQ(UpdateWarehouseItem(prod1_.id, 15), 0);
//     EXPECT_EQ(retrieved_product->stock, 25);
//     EXPECT_EQ(UpdateWarehouseItem(prod1_.id, 5), 0);
//     EXPECT_EQ(retrieved_product->stock, 30);
// }

// TEST_F(WarehouseListTest, RemoveItemStock)
// {
//     EXPECT_EQ(ProductAddToRegistry(&prod1_), 0);
//     Product *retrieved_product = ProductGetById(prod1_.id);
//     ASSERT_NE(retrieved_product, nullptr);

//     EXPECT_EQ(UpdateWarehouseItem(prod1_.id, 20), 0);
//     EXPECT_EQ(retrieved_product->stock, 20);

//     EXPECT_EQ(UpdateWarehouseItem(prod1_.id, -5), 0);
//     EXPECT_EQ(retrieved_product->stock, 15);
// }

// TEST_F(WarehouseListTest, RemoveItemStockBelowZero)
// {
//     EXPECT_EQ(ProductAddToRegistry(&prod1_), 0);
//     Product *retrieved_product = ProductGetById(prod1_.id);
//     ASSERT_NE(retrieved_product, nullptr);

//     EXPECT_EQ(UpdateWarehouseItem(prod1_.id, 5), 0);
//     EXPECT_EQ(retrieved_product->stock, 5);

//     EXPECT_NE(UpdateWarehouseItem(prod1_.id, -10), 0);
//     EXPECT_EQ(retrieved_product->stock, 5);
// }

} // namespace