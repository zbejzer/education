#include <cstring>
#include <gtest/gtest.h>
#include <string>

extern "C"
{
#include "config.h"
#include "input_processor.h"
}

namespace
{

std::string build_joint_category(const unsigned int category, const unsigned int subcategory)
{
    std::string joint_category = std::to_string(category);

    if (subcategory != SUBCATEGORY_WILDCARD)
    {
        joint_category += "." + std::to_string(subcategory);
    }

    return joint_category;
};

std::string build_command_line(const std::string cmd, const std::string args)
{
    return cmd + " " + args;
}

std::string build_update_entry(const std::string id, const char operation, const int stock_change)
{
    std::string operation_str = "";
    operation_str.push_back(operation);
    return id + " " + operation_str + " " + std::to_string(stock_change);
};

std::string build_init_entry(const std::string id, const std::string name, const unsigned int category,
                             unsigned int subcategory, const unsigned int flammability)
{
    return build_joint_category(category, subcategory) + " " + std::to_string(flammability) + " " + id + " " + name;
};

std::string build_create_header(const std::string id, const unsigned int stock_max, const unsigned int flammability,
                                const std::string name)
{
    return id + " " + std::to_string(stock_max) + " " + std::to_string(flammability) + " " + name;
};

std::string build_create_entry(const unsigned int category, const unsigned int subcategory,
                               const unsigned int stock_max, const unsigned int stock_min_threshold)
{
    return build_joint_category(category, subcategory) + " " + std::to_string(stock_max) + " " +
           std::to_string(stock_min_threshold);
};

TEST(SanitizeRawLineTest, NoPadding)
{
    struct
    {
        const std::string input;
        const std::string output;
    } test_data[] = {{"3", "3"},
                     {"4.3 4 AB234 R12", "4.3 4 AB234 R12"},
                     {"4.5 4 SD121 R20", "4.5 4 SD121 R20"},
                     {"4 4 RS001 Zestaw baterii", "4 4 RS001 Zestaw baterii"}};

    for (auto &&i : test_data)
    {
        char *cstr = new char[i.input.length() + 1];
        std::strcpy(cstr, i.input.c_str());
        SanitizeRawLine(cstr);

        EXPECT_STREQ(cstr, i.output.c_str()) << "Failed for input: " << i.input;

        delete[] cstr;
    }
}

TEST(SanitizeRawLineTest, Padding)
{
    struct
    {
        const std::string input;
        const std::string output;
    } test_data[] = {{"3\n", "3"},
                     {"4.3 4 AB234 R12\n", "4.3 4 AB234 R12"},
                     {"4.5 4 SD121 R20\n", "4.5 4 SD121 R20"},
                     {"4 4 RS001 Zestaw baterii\n", "4 4 RS001 Zestaw baterii"}};

    for (auto &&i : test_data)
    {
        char *cstr = new char[i.input.length() + 1];
        std::strcpy(cstr, i.input.c_str());
        SanitizeRawLine(cstr);

        EXPECT_STREQ(cstr, i.output.c_str()) << "Failed for input: " << i.input;

        delete[] cstr;
    }
}

TEST(ParseCommandLineTest, NoArgs)
{
    struct
    {
        const std::string cmd;
        const std::string args;
    } test_data[] = {{"init", ""}, {"update", ""}, {"create", ""}, {"transfer", ""}};

    for (auto &i : test_data)
    {
        char *res_cmd = new char[i.cmd.size() * 2];
        char *res_args = new char[i.args.size() * 2];

        ParseCommandLine(build_command_line(i.cmd, i.args).c_str(), res_cmd, res_args);

        EXPECT_STREQ(res_cmd, i.cmd.c_str()) << "Parsed command failed for input: " << i.cmd;
        EXPECT_STREQ(res_args, i.args.c_str()) << "Parsed arguments failed for input: " << i.args;

        delete[] res_cmd;
        delete[] res_args;
    }
}

TEST(ParseCommandLineTest, SingleArgs)
{
    struct
    {
        const std::string cmd;
        const std::string args;
    } test_data[] = {{"init", "i.txt"}, {"update", "u.txt"}, {"create", "c.txt"}, {"transfer", "t.txt"}};

    for (auto &i : test_data)
    {
        char *res_cmd = new char[i.cmd.size() * 2];
        char *res_args = new char[i.args.size() * 2];

        ParseCommandLine(build_command_line(i.cmd, i.args).c_str(), res_cmd, res_args);

        EXPECT_STREQ(res_cmd, i.cmd.c_str()) << "Parsed command failed for input: " << i.cmd;
        EXPECT_STREQ(res_args, i.args.c_str()) << "Parsed arguments failed for input: " << i.args;

        delete[] res_cmd;
        delete[] res_args;
    }
}

TEST(ParseCommandLineTest, DoubleArgs)
{
    struct
    {
        const std::string cmd;
        const std::string args;
    } test_data[] = {{"print", "file -SC"}, {"print", "file -FL"}, {"print", "file -F[1, 2,. 3]"}};

    for (auto &i : test_data)
    {
        char *res_cmd = new char[i.cmd.size() * 2];
        char *res_args = new char[i.args.size() * 2];
        const std::string built_data = build_command_line(i.cmd, i.args);

        ParseCommandLine(built_data.c_str(), res_cmd, res_args);

        EXPECT_STREQ(res_cmd, i.cmd.c_str()) << "Parsed command failed for input: " << built_data;
        EXPECT_STREQ(res_args, i.args.c_str()) << "Parsed arguments failed for input: " << built_data;

        delete[] res_cmd;
        delete[] res_args;
    }
}

TEST(ParseLineCountTest, PositiveNumbers)
{
    const int test_data[] = {0, 1, 6, 10};

    for (auto &i : test_data)
    {
        const std::string built_data = std::to_string(i);
        int res_count = INT_MAX;

        ParseLineCount(built_data.c_str(), &res_count);
        EXPECT_EQ(res_count, i) << "Failed for input: " << built_data;
    }
}

TEST(ParseLineCountTest, NegativeNumbers)
{
    const int test_data[] = {-10, -1, -6, -20};

    for (auto &i : test_data)
    {
        const std::string built_data = std::to_string(i);
        int res_count = INT_MAX;

        ParseLineCount(built_data.c_str(), &res_count);
        EXPECT_EQ(res_count, i) << "Failed for input: " << built_data;
    }
}

TEST(ParseUpdateTest, UpdateHeader)
{
    const std::string test_data[] = {"MG252", "MG251", "AB234", "RS001"};

    for (auto &i : test_data)
    {
        char *res_id = new char[i.size() * 2];

        ParseUpdateHeader(i.c_str(), res_id);
        EXPECT_STREQ(res_id, i.c_str()) << "Failed for input: " << i;

        delete[] res_id;
    }
}

TEST(ParseUpdateTest, UpdateEntry)
{
    struct
    {
        const std::string id;
        const char operation;
        const int stock_change;
    } test_data[] = {{"AB234", '+', 8}, {"RS001", '-', 2}};

    for (auto &i : test_data)
    {
        char *res_id = new char[i.id.size() * 2];
        char res_operation;
        int res_stock_change;
        const std::string built_data = build_update_entry(i.id, i.operation, i.stock_change);

        ParseUpdateEntry(built_data.c_str(), res_id, &res_operation, &res_stock_change);
        EXPECT_STREQ(res_id, i.id.c_str()) << "Product ID failed for input: " << built_data;
        EXPECT_EQ(res_operation, i.operation) << "Operation failed for input: " << built_data;
        EXPECT_EQ(res_stock_change, i.stock_change) << "Stock change failed for input: " << built_data;

        delete[] res_id;
    }
}

TEST(ParseInitEntryTest, EmptySubcategory)
{
    const Product test_data[] = {
        {"AB123", "ProdWithNoSpaces", 10, SUBCATEGORY_WILDCARD, 0},
        {"CD356", "ProdWith1Number", 6, SUBCATEGORY_WILDCARD, 3},
        {"EF789", "Prod With Spaces", 4, SUBCATEGORY_WILDCARD, 7},
        {"GH112", "Prod With Spaces And 1 Number", 0, SUBCATEGORY_WILDCARD, 10},
    };

    for (auto &i : test_data)
    {
        Product result_product = {"", "", UINT_MAX, 0, UINT_MAX};
        const std::string built_data = build_init_entry(i.id, i.name, i.category, i.subcategory, i.flammability);

        ParseInitEntry(built_data.c_str(), &result_product);
        EXPECT_EQ(result_product.category, i.category) << "Category failed for input: " << built_data;
        EXPECT_EQ(result_product.subcategory, i.subcategory) << "Subcategory failed for input: " << built_data;
        EXPECT_EQ(result_product.flammability, i.flammability) << "Flammability failed for input: " << built_data;
        EXPECT_STREQ(result_product.id, i.id) << "ID failed for input: " << built_data;
        EXPECT_STREQ(result_product.name, i.name) << "Name failed for input: " << built_data;
    }
}

TEST(ParseInitEntryTest, CategoryAndSubcategory)
{
    const Product test_data[] = {
        {"AB123", "ProdWithNoSpaces", 10, 5, 0},
        {"CD356", "ProdWith1Number", 6, 4, 3},
        {"EF789", "Prod With Spaces", 4, 0, 7},
        {"GH112", "Prod With Spaces And 1 Number", 0, 4, 10},
    };

    for (auto &i : test_data)
    {
        Product result_product = {"", "", UINT_MAX, 0, UINT_MAX};
        const std::string built_data = build_init_entry(i.id, i.name, i.category, i.subcategory, i.flammability);

        ParseInitEntry(built_data.c_str(), &result_product);
        EXPECT_EQ(result_product.category, i.category) << "Category failed for input: " << built_data;
        EXPECT_EQ(result_product.subcategory, i.subcategory) << "Subcategory failed for input: " << built_data;
        EXPECT_EQ(result_product.flammability, i.flammability) << "Flammability failed for input: " << built_data;
        EXPECT_STREQ(result_product.id, i.id) << "ID failed for input: " << built_data;
        EXPECT_STREQ(result_product.name, i.name) << "Name failed for input: " << built_data;
    }
}

TEST(ParseJointCategoryTest, EmptySubcategory)
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

TEST(ParseJointCategoryTest, CategoryAndSubcategory)
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

TEST(ParseCreateHeaderTest, CreateHeader)
{
    const Warehouse test_data[] = {
        {"AB123", "WhsWithNoSpaces", 100, 0, WarehouseSectionList(), ProductStockList()},
        {"CD356", "WhsWith1Number", 6, 3, WarehouseSectionList(), ProductStockList()},
        {"EF789", "Whs With Spaces", 40, 7, WarehouseSectionList(), ProductStockList()},
        {"GH112", "Whs With Spaces And 1 Number", 0, 10, WarehouseSectionList(), ProductStockList()},
    };

    for (auto &i : test_data)
    {
        Warehouse res_warehouse = {"", "", UINT_MAX, UINT_MAX, WarehouseSectionList(), ProductStockList()};
        const std::string built_data = build_create_header(i.id, i.stock_max, i.flammability_max, i.name);

        ParseCreateHeader(built_data.c_str(), &res_warehouse);
        EXPECT_STREQ(res_warehouse.id, i.id) << "ID failed for input: " << built_data;
        EXPECT_EQ(res_warehouse.stock_max, i.stock_max) << "Stock max failed for input: " << built_data;
        EXPECT_EQ(res_warehouse.flammability_max, i.flammability_max)
            << "Flammability failed for input: " << built_data;
        EXPECT_STREQ(res_warehouse.name, i.name) << "Name failed for input: " << built_data;
    }
}

TEST(ParseCreateTest, EmptySubcategory)
{
    const WarehouseSection test_data[] = {
        {100, 18, 4, UINT_MAX},
        {6, 3, 7, UINT_MAX},
        {40, 23, 9, UINT_MAX},
        {0, 0, 0, UINT_MAX},
    };

    for (auto &i : test_data)
    {
        WarehouseSection res_section = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
        const std::string built_data =
            build_create_entry(i.category, i.subcategory, i.stock_max, i.stock_min_threshold);

        ParseCreateEntry(built_data.c_str(), &res_section);
        EXPECT_EQ(res_section.stock_max, i.stock_max) << "Stock max failed for input: " << built_data;
        EXPECT_EQ(res_section.stock_min_threshold, i.stock_min_threshold)
            << "Stock min threshold failed for input: " << built_data;
        EXPECT_EQ(res_section.category, i.category) << "Category failed for input: " << built_data;
        EXPECT_EQ(res_section.subcategory, i.subcategory) << "Subcategory failed for input: " << built_data;
    }
}

TEST(ParseCreateTest, CategoryAndSubcategory)
{
    const WarehouseSection test_data[] = {
        {100, 18, 4, 7},
        {6, 3, 7, 5},
        {40, 23, 9, 9},
        {0, 0, 0, 0},
    };

    for (auto &i : test_data)
    {
        WarehouseSection res_section = {UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX};
        const std::string built_data =
            build_create_entry(i.category, i.subcategory, i.stock_max, i.stock_min_threshold);

        ParseCreateEntry(built_data.c_str(), &res_section);
        EXPECT_EQ(res_section.stock_max, i.stock_max) << "Stock max failed for input: " << built_data;
        EXPECT_EQ(res_section.stock_min_threshold, i.stock_min_threshold)
            << "Stock min threshold failed for input: " << built_data;
        EXPECT_EQ(res_section.category, i.category) << "Category failed for input: " << built_data;
        EXPECT_EQ(res_section.subcategory, i.subcategory) << "Subcategory failed for input: " << built_data;
    }
}

} // namespace