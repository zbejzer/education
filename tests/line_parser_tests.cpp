#include <gtest/gtest.h>
#include <ranges>
#include <string>

extern "C"
{
#include "config.h"
#include "line_parser.h"
}

namespace
{

std::string build_joint_category(const unsigned int category, unsigned int subcategory)
{
    return std::to_string(category) + "." + std::to_string(subcategory);
};

std::string build_simple_product(const std::string id, const std::string name, const unsigned int flammability,
                                 const unsigned int category)
{
    return std::to_string(category) + " " + std::to_string(flammability) + " " + id + " " + name;
};

std::string build_full_product(const std::string id, const std::string name, const unsigned int category,
                               unsigned int subcategory, const unsigned int flammability)
{
    return build_joint_category(category, subcategory) + " " + std::to_string(flammability) + " " + id + " " + name;
};

TEST(CategoryParserTest, EmptySubcategory)
{
    const unsigned int test_data[] = {0, 1, 6, 10};

    for (auto &i : test_data)
    {
        const std::string built_data = std::to_string(i);
        unsigned int result_category = UINT_MAX;
        unsigned int result_subcategory = 0;
        ParseJointCategory(built_data.c_str(), &result_category, &result_subcategory);
        EXPECT_EQ(result_category, i) << "Category failed for input: " << built_data;
        EXPECT_EQ(result_subcategory, SUBCATEGORY_WILDCARD) << "Subcategory failed for input: " << built_data;
    }
}

TEST(CategoryParserTest, CategoryAndSubcategory)
{
    struct
    {
        unsigned int category;
        unsigned int subcategory;
    } test_data[] = {
        {0, 0}, {0, 6}, {0, 10}, {6, 0}, {6, 6}, {6, 10}, {10, 0}, {10, 6}, {10, 10},
    };

    for (auto &i : test_data)
    {
        const std::string built_data = build_joint_category(i.category, i.subcategory);
        unsigned int result_category = UINT_MAX;
        unsigned int result_subcategory = 0;
        ParseJointCategory(built_data.c_str(), &result_category, &result_subcategory);
        EXPECT_EQ(result_category, i.category) << "Category failed for input: " << built_data;
        EXPECT_EQ(result_subcategory, i.subcategory) << "Subcategory failed for input: " << built_data;
    }
}

TEST(ProductParserTest, EmptySubcategory)
{
    const Product test_data[] = {
        {.id = "AB123",
         .name = "ProdWithNoSpaces",
         .category = 10,
         .subcategory = SUBCATEGORY_WILDCARD,
         .flammability = 0},
        {.id = "CD356",
         .name = "ProdWith1Number",
         .category = 6,
         .subcategory = SUBCATEGORY_WILDCARD,
         .flammability = 3},
        {.id = "EF789",
         .name = "Prod With Spaces",
         .category = 4,
         .subcategory = SUBCATEGORY_WILDCARD,
         .flammability = 7},
        {.id = "GH112",
         .name = "Prod With Spaces And 1 Number",
         .category = 0,
         .subcategory = SUBCATEGORY_WILDCARD,
         .flammability = 10},
    };

    for (auto &i : test_data)
    {
        Product result_product = {
            .id = "", .name = "", .category = UINT_MAX, .subcategory = 0, .flammability = UINT_MAX};
        const std::string built_data = build_simple_product(i.id, i.name, i.flammability, i.category);
        ParseProductLine(built_data.c_str(), &result_product);
        EXPECT_EQ(result_product.category, i.category) << "Category failed for input: " << built_data;
        EXPECT_EQ(result_product.subcategory, i.subcategory) << "Subcategory failed for input: " << built_data;
        EXPECT_EQ(result_product.flammability, i.flammability) << "Flammability failed for input: " << built_data;
        EXPECT_STREQ(result_product.id, i.id) << "ID failed for input: " << built_data;
        EXPECT_STREQ(result_product.name, i.name) << "Name failed for input: " << built_data;
    }
}

TEST(ProductParserTest, CategoryAndSubcategory)
{
    const Product test_data[] = {
        {.id = "AB123", .name = "ProdWithNoSpaces", .category = 10, .subcategory = 5, .flammability = 0},
        {.id = "CD356", .name = "ProdWith1Number", .category = 6, .subcategory = 4, .flammability = 3},
        {.id = "EF789", .name = "Prod With Spaces", .category = 4, .subcategory = 0, .flammability = 7},
        {.id = "GH112", .name = "Prod With Spaces And 1 Number", .category = 0, .subcategory = 4, .flammability = 10},
    };

    for (auto &i : test_data)
    {
        Product result_product = {
            .id = "", .name = "", .category = UINT_MAX, .subcategory = 0, .flammability = UINT_MAX};
        const std::string built_data = build_full_product(i.id, i.name, i.category, i.subcategory, i.flammability);
        ParseProductLine(built_data.c_str(), &result_product);
        EXPECT_EQ(result_product.category, i.category) << "Category failed for input: " << built_data;
        EXPECT_EQ(result_product.subcategory, i.subcategory) << "Subcategory failed for input: " << built_data;
        EXPECT_EQ(result_product.flammability, i.flammability) << "Flammability failed for input: " << built_data;
        EXPECT_STREQ(result_product.id, i.id) << "ID failed for input: " << built_data;
        EXPECT_STREQ(result_product.name, i.name) << "Name failed for input: " << built_data;
    }
}

} // namespace