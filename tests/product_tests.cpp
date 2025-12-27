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
        : prod1_({.id = "AB123", .name = "Product 1", .category = 1, .subcategory = 3, .flammability = 5}), //
          prod2_({.id = "CD456",
                  .name = "Product 2",
                  .category = 2,
                  .subcategory = SUBCATEGORY_WILDCARD,
                  .flammability = 6}),                                                                     //
          prod3_({.id = "EF789", .name = "Product 3", .category = 7, .subcategory = 4, .flammability = 2}) //
    {
        ProductListClear();
    }

    ~ProductTest() override
    {
        ProductListClear();
    }
};

TEST_F(ProductTest, ClearNonEmptyProductList)
{
    kProducts.data = (Product *)malloc(sizeof(Product) * 3);
    kProducts.size = 3;

    ASSERT_NE(kProducts.data, nullptr);

    ProductCopy(&kProducts.data[0], &prod1_);
    ProductCopy(&kProducts.data[1], &prod2_);
    ProductCopy(&kProducts.data[2], &prod3_);

    ProductListClear();

    EXPECT_EQ(kProducts.size, 0);
    EXPECT_EQ(kProducts.data, nullptr);
}

TEST_F(ProductTest, ClearEmptyProductList)
{
    ASSERT_EQ(kProducts.data, nullptr);
    ASSERT_EQ(kProducts.size, 0);
    EXPECT_EQ(ProductListClear(), 0);
    EXPECT_EQ(kProducts.data, nullptr);
    EXPECT_EQ(kProducts.size, 0);
}

TEST_F(ProductTest, CopyProduct)
{
    Product dst_product = {.id = "XY987", .name = "DstProd", .category = 7, .subcategory = 8, .flammability = 9};
    ASSERT_NE(prod1_.id, dst_product.id);
    ASSERT_NE(prod1_.name, dst_product.name);
    ASSERT_STRNE(prod1_.id, dst_product.id);
    ASSERT_STRNE(prod1_.name, dst_product.name);
    ASSERT_NE(prod1_.category, dst_product.category);
    ASSERT_NE(prod1_.subcategory, dst_product.subcategory);
    ASSERT_NE(prod1_.flammability, dst_product.flammability);

    EXPECT_EQ(ProductCopy(&dst_product, &prod1_), 0);
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

    ProductCopy(&kProducts.data[0], &prod1_);
    ProductCopy(&kProducts.data[1], &prod2_);
    ProductCopy(&kProducts.data[2], &prod3_);

    EXPECT_EQ(ProductGetById(prod3_.id), &kProducts.data[2]);
    EXPECT_EQ(ProductGetById(prod1_.id), &kProducts.data[0]);
    EXPECT_EQ(ProductGetById(prod2_.id), &kProducts.data[1]);
}

TEST_F(ProductTest, RetrieveNonExistentItem)
{
    kProducts.data = (Product *)malloc(sizeof(Product) * 3);
    kProducts.size = 3;

    ASSERT_NE(kProducts.data, nullptr);

    ProductCopy(&kProducts.data[0], &prod1_);
    ProductCopy(&kProducts.data[1], &prod2_);
    ProductCopy(&kProducts.data[2], &prod3_);

    EXPECT_EQ(ProductGetById("ZZ999"), nullptr);
    EXPECT_EQ(ProductGetById("XY987"), nullptr);
    EXPECT_EQ(ProductGetById("AB789"), nullptr);
}

} // namespace