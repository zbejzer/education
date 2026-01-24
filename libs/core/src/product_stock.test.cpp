#include <gtest/gtest.h>

extern "C"
{
#include "product_stock.h"
}

namespace
{

class ProductStockListTest : public testing::Test
{
  protected:
    ProductStockList test_stock_list_;
    Product product_a_, product_b_, product_c_;
    ProductStock product_stock_a_, product_stock_b_, product_stock_c_;

    ProductStockListTest()
        : product_a_({"AB123", "Product 1", 1, 3, 5}), product_b_({"CD456", "Product 2", 2, SUBCATEGORY_WILDCARD, 6}),
          product_c_({"EF789", "Product 3", 1, 4, 2})
    {
        ProductStockListInit(&test_stock_list_);
        product_stock_a_.product = &product_a_;
        product_stock_a_.stock = 30;
        product_stock_b_.product = &product_b_;
        product_stock_b_.stock = 10;
        product_stock_c_.product = &product_c_;
        product_stock_c_.stock = 20;
    }

    ~ProductStockListTest() override
    {
        ProductStockListClear(&test_stock_list_);
    }
};

TEST_F(ProductStockListTest, ClearNonEmpty)
{
    ProductStockNode *product_stock_node_a_ = new ProductStockNode;
    ProductStockNode *product_stock_node_b_ = new ProductStockNode;
    ProductStockNode *product_stock_node_c_ = new ProductStockNode;

    *product_stock_node_a_ = {product_stock_node_b_, product_stock_a_};
    *product_stock_node_b_ = {product_stock_node_c_, product_stock_b_};
    *product_stock_node_c_ = {nullptr, product_stock_c_};

    test_stock_list_.front = product_stock_node_a_;
    test_stock_list_.back = product_stock_node_c_;
    test_stock_list_.size = 3;

    ASSERT_EQ(ProductStockListClear(&test_stock_list_), 0);

    EXPECT_EQ(test_stock_list_.size, 0);
    EXPECT_EQ(test_stock_list_.front, nullptr);
    EXPECT_EQ(test_stock_list_.back, nullptr);
}

TEST_F(ProductStockListTest, ClearEmpty)
{
    ASSERT_EQ(test_stock_list_.front, nullptr);
    ASSERT_EQ(test_stock_list_.back, nullptr);
    ASSERT_EQ(test_stock_list_.size, 0);

    ASSERT_EQ(ProductStockListClear(&test_stock_list_), 0);

    EXPECT_EQ(test_stock_list_.front, nullptr);
    EXPECT_EQ(test_stock_list_.back, nullptr);
    EXPECT_EQ(test_stock_list_.size, 0);
}

TEST_F(ProductStockListTest, Push)
{
    ProductStockListPush(&test_stock_list_, &product_stock_a_);
    EXPECT_NE(test_stock_list_.front, nullptr);
    EXPECT_NE(test_stock_list_.back, nullptr);
    EXPECT_EQ(test_stock_list_.size, 1);

    ProductStockListPush(&test_stock_list_, &product_stock_b_);
    EXPECT_NE(test_stock_list_.front, nullptr);
    EXPECT_NE(test_stock_list_.back, nullptr);
    EXPECT_EQ(test_stock_list_.front->next, test_stock_list_.back);
    EXPECT_NE(test_stock_list_.front, test_stock_list_.back);
    EXPECT_EQ(test_stock_list_.size, 2);
}

TEST_F(ProductStockListTest, GetTotalStock)
{
    ProductStockListPush(&test_stock_list_, &product_stock_a_);
    ProductStockListPush(&test_stock_list_, &product_stock_b_);
    ProductStockListPush(&test_stock_list_, &product_stock_c_);

    EXPECT_EQ(ProductStockListGetTotalStock(&test_stock_list_), 60);
}

TEST_F(ProductStockListTest, GetCategoryStockWithoutSubcategories)
{
    ProductStockListPush(&test_stock_list_, &product_stock_a_);
    ProductStockListPush(&test_stock_list_, &product_stock_b_);
    ProductStockListPush(&test_stock_list_, &product_stock_c_);

    EXPECT_EQ(ProductStockListGetCategoryStock(&test_stock_list_, 2, SUBCATEGORY_WILDCARD), 10);
}

TEST_F(ProductStockListTest, GetCategoryStockWithSubcategories)
{
    ProductStockListPush(&test_stock_list_, &product_stock_a_);
    ProductStockListPush(&test_stock_list_, &product_stock_b_);
    ProductStockListPush(&test_stock_list_, &product_stock_c_);

    EXPECT_EQ(ProductStockListGetCategoryStock(&test_stock_list_, 1, SUBCATEGORY_WILDCARD), 50);
}

TEST_F(ProductStockListTest, GetByProduct)
{
    ProductStockListPush(&test_stock_list_, &product_stock_a_);
    ProductStockListPush(&test_stock_list_, &product_stock_b_);
    ProductStockListPush(&test_stock_list_, &product_stock_c_);

    EXPECT_EQ(ProductStockListGetByProduct(&test_stock_list_, &product_b_)->product, &product_b_);
}

} // namespace