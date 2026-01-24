#include <gtest/gtest.h>

extern "C"
{
#include "warehouse_section.h"
}

namespace
{

class WarehouseSectionListTest : public testing::Test
{
  protected:
    WarehouseSectionList test_section_list_;

    WarehouseSectionListTest()
    {
        WarehouseSectionListInit(&test_section_list_);
        test_section_list_.size = 5;
        test_section_list_.data = new WarehouseSection[4];
        test_section_list_.data[0] = {30, 10, 4, 3};
        test_section_list_.data[1] = {50, 10, 4, 5};
        test_section_list_.data[2] = {400, 10, 4, SUBCATEGORY_WILDCARD};
        test_section_list_.data[3] = {500, 10, 5, SUBCATEGORY_WILDCARD};
    }

    ~WarehouseSectionListTest() override
    {
        delete[] test_section_list_.data;
    }
};

TEST_F(WarehouseSectionListTest, GetSectionValidCategoryWithNoSubcategories)
{
    EXPECT_EQ(WarehouseSectionListGetSection(&test_section_list_, 5), &test_section_list_.data[3]);
}

TEST_F(WarehouseSectionListTest, GetSectionValidCategoryWithExistingSubcategories)
{
    EXPECT_EQ(WarehouseSectionListGetSection(&test_section_list_, 4), &test_section_list_.data[2]);
}

TEST_F(WarehouseSectionListTest, GetSectionInvalidCategory)
{
    EXPECT_EQ(WarehouseSectionListGetSection(&test_section_list_, 2), nullptr);
}

TEST_F(WarehouseSectionListTest, GetSubsectionValidCategoryWithValidSubcategory)
{
    EXPECT_EQ(WarehouseSectionListGetSubsection(&test_section_list_, 4, 5), &test_section_list_.data[1]);
}

TEST_F(WarehouseSectionListTest, GetSubsectionValidCategoryWithInvalidSubcategory)
{
    EXPECT_EQ(WarehouseSectionListGetSubsection(&test_section_list_, 4, 4), nullptr);
}

TEST_F(WarehouseSectionListTest, GetSubsectionInvalidCategoryWithValidSubcategory)
{
    EXPECT_EQ(WarehouseSectionListGetSubsection(&test_section_list_, 6, 5), nullptr);
}

TEST_F(WarehouseSectionListTest, GetSubsectionInvalidCategoryWithInvalidSubcategory)
{
    EXPECT_EQ(WarehouseSectionListGetSubsection(&test_section_list_, 6, 4), nullptr);
}

TEST_F(WarehouseSectionListTest, GetSubsectionValidCategoryWithNoSubcategories)
{
    EXPECT_EQ(WarehouseSectionListGetSubsection(&test_section_list_, 5, 5), nullptr);
}

} // namespace