
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

    ASSERT_EQ(WarehouseListClear(&kWarehouses), 0);

    EXPECT_EQ(kWarehouses.size, 0);
    EXPECT_EQ(kWarehouses.front, nullptr);
    EXPECT_EQ(kWarehouses.back, nullptr);
}

TEST_F(WarehouseListTest, ClearEmpty)
{
    ASSERT_EQ(kWarehouses.front, nullptr);
    ASSERT_EQ(kWarehouses.back, nullptr);
    ASSERT_EQ(kWarehouses.size, 0);

    ASSERT_EQ(WarehouseListClear(&kWarehouses), 0);

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

TEST_F(WarehouseListTest, GetById)
{
    ASSERT_EQ(WarehouseListPush(warehouse_node_1_), 0);
    ASSERT_EQ(WarehouseListPush(warehouse_node_2_), 0);
    ASSERT_EQ(WarehouseListPush(warehouse_node_3_), 0);

    EXPECT_EQ(WarehouseListGetById(warehouse_node_2_->data.id), &warehouse_node_2_->data);
    EXPECT_EQ(WarehouseListGetById(warehouse_node_1_->data.id), &warehouse_node_1_->data);
    EXPECT_EQ(WarehouseListGetById(warehouse_node_3_->data.id), &warehouse_node_3_->data);
    EXPECT_EQ(WarehouseListGetById("XX999"), nullptr);
}

} // namespace