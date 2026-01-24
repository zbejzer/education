#include <gtest/gtest.h>

extern "C"
{
#include "config.h"
#include "product.h"
}

namespace
{

class ProductTest : public testing::Test
{
  protected:
    const Product prod1_;
    const Product prod2_;
    const Product prod3_;

    ProductTest()
        : prod1_({"AB123", "Product 1", 1, 3, 5}),                    //
          prod2_({"CD456", "Product 2", 2, SUBCATEGORY_WILDCARD, 6}), //
          prod3_({"EF789", "Product 3", 7, 4, 2})                     //
    {
        ProductListClear(&kProducts);
    }

    ~ProductTest() override
    {
        ProductListClear(&kProducts);
    }
};

TEST_F(ProductTest, ClearNonEmptyProductList)
{
    kProducts.data = (Product *)malloc(sizeof(Product) * 3);
    kProducts.size = 3;

    ASSERT_NE(kProducts.data, nullptr);

    ASSERT_EQ(ProductCopy(&kProducts.data[0], &prod1_), 0);
    ASSERT_EQ(ProductCopy(&kProducts.data[1], &prod2_), 0);
    ASSERT_EQ(ProductCopy(&kProducts.data[2], &prod3_), 0);

    ASSERT_EQ(ProductListClear(&kProducts), 0);

    EXPECT_EQ(kProducts.size, 0);
    EXPECT_EQ(kProducts.data, nullptr);
}

TEST_F(ProductTest, ClearEmptyProductList)
{
    ASSERT_EQ(kProducts.data, nullptr);
    ASSERT_EQ(kProducts.size, 0);

    ASSERT_EQ(ProductListClear(&kProducts), 0);

    EXPECT_EQ(kProducts.data, nullptr);
    EXPECT_EQ(kProducts.size, 0);
}

TEST_F(ProductTest, CopyProduct)
{
    Product dst_product = {"XY987", "DstProd", 7, 8, 9};
    ASSERT_NE(prod1_.id, dst_product.id);
    ASSERT_NE(prod1_.name, dst_product.name);
    ASSERT_STRNE(prod1_.id, dst_product.id);
    ASSERT_STRNE(prod1_.name, dst_product.name);
    ASSERT_NE(prod1_.category, dst_product.category);
    ASSERT_NE(prod1_.subcategory, dst_product.subcategory);
    ASSERT_NE(prod1_.flammability, dst_product.flammability);

    ASSERT_EQ(ProductCopy(&dst_product, &prod1_), 0);

    EXPECT_NE(prod1_.id, dst_product.id);
    EXPECT_NE(prod1_.name, dst_product.name);
    EXPECT_STREQ(prod1_.id, dst_product.id);
    EXPECT_STREQ(prod1_.name, dst_product.name);
    EXPECT_EQ(prod1_.category, dst_product.category);
    EXPECT_EQ(prod1_.subcategory, dst_product.subcategory);
    EXPECT_EQ(prod1_.flammability, dst_product.flammability);
}

TEST_F(ProductTest, RetrieveExistingItem)
{
    kProducts.data = (Product *)malloc(sizeof(Product) * 3);
    kProducts.size = 3;

    ASSERT_NE(kProducts.data, nullptr);

    ASSERT_EQ(ProductCopy(&kProducts.data[0], &prod1_), 0);
    ASSERT_EQ(ProductCopy(&kProducts.data[1], &prod2_), 0);
    ASSERT_EQ(ProductCopy(&kProducts.data[2], &prod3_), 0);

    EXPECT_EQ(ProductListGetById(prod3_.id), &kProducts.data[2]);
    EXPECT_EQ(ProductListGetById(prod1_.id), &kProducts.data[0]);
    EXPECT_EQ(ProductListGetById(prod2_.id), &kProducts.data[1]);
}

TEST_F(ProductTest, RetrieveNonExistentItem)
{
    kProducts.data = (Product *)malloc(sizeof(Product) * 3);
    kProducts.size = 3;

    ASSERT_NE(kProducts.data, nullptr);

    ASSERT_EQ(ProductCopy(&kProducts.data[0], &prod1_), 0);
    ASSERT_EQ(ProductCopy(&kProducts.data[1], &prod2_), 0);
    ASSERT_EQ(ProductCopy(&kProducts.data[2], &prod3_), 0);

    EXPECT_EQ(ProductListGetById("ZZ999"), nullptr);
    EXPECT_EQ(ProductListGetById("XY987"), nullptr);
    EXPECT_EQ(ProductListGetById("AB789"), nullptr);
}

} // namespace