#include <gtest/gtest.h>

extern "C"
{
#include "validator.h"
}

namespace
{

TEST(ProductCountValidation, Valid)
{
    const int test_data[] = {1, 1000, 9, 257, 513};
    for (auto &&test : test_data)
    {
        EXPECT_EQ(ValidateProductsCount(test), 0) << "Failed for input: " << test;
    }
}

TEST(ProductCountValidation, InvalidPositive)
{
    const int test_data[] = {0, 1001, 21321231, 44545444, 1203};
    for (auto &&test : test_data)
    {
        EXPECT_NE(ValidateProductsCount(test), 0) << "Failed for input: " << test;
    }
}

TEST(ProductCountValidation, InvalidNegative)
{
    const int test_data[] = {-1, -1001, -21321231, -44545444, -1203};
    for (auto &&test : test_data)
    {
        EXPECT_NE(ValidateProductsCount(test), 0) << "Failed for input: " << test;
    }
}

TEST(ProductIdValidation, Valid)
{
    const std::string test_data[] = {"AB234", "SD121", "RS001", "AB235", "CD898"};
    for (auto &&test : test_data)
    {
        EXPECT_EQ(ValidateProductId(test.c_str()), 0) << "Failed for input: " << test;
    }
}

TEST(ProductIdValidation, InvalidCharacters)
{
    const std::string test_data[] = {"Aa234", "sD121", "RSR01", "D1S21", "2AB35", "898CD"};
    for (auto &&test : test_data)
    {
        EXPECT_NE(ValidateProductId(test.c_str()), 0) << "Failed for input: " << test;
    }
}

TEST(ProductIdValidation, InvalidLength)
{
    const std::string test_data[] = {"AB2345", "SDS121", "001RSR", "23ABB5", "CD8D98"};
    for (auto &&test : test_data)
    {
        EXPECT_NE(ValidateProductId(test.c_str()), 0) << "Failed for input: " << test;
    }
}

TEST(ProductNameValidation, Valid)
{
    const std::string test_data[] = {"R12", "R20", "Zestaw baterii", "A5 Zeszyt", "Zeszyt 100 kartek"};
    for (auto &&test : test_data)
    {
        EXPECT_EQ(ValidateProductName(test.c_str()), 0) << "Failed for input: " << test;
    }
}

TEST(ProductNameValidation, Invalid)
{
    const std::string test_data[] = {"123", "Gadget_XYZ", "Tool-Set"};
    for (auto &&test : test_data)
    {
        EXPECT_NE(ValidateProductName(test.c_str()), 0) << "Failed for input: " << test;
    }
}

TEST(WarehouseSectionCountValidation, Valid)
{
    const int test_data[] = {1, 100, 9, 25, 51};
    for (auto &&test : test_data)
    {
        EXPECT_EQ(ValidateWarehouseSectionCount(test), 0) << "Failed for input: " << test;
    }
}

TEST(WarehouseSectionCountValidation, InvalidPositive)
{
    const int test_data[] = {0, 101, 2132, 44545444, 1003};
    for (auto &&test : test_data)
    {
        EXPECT_NE(ValidateWarehouseSectionCount(test), 0) << "Failed for input: " << test;
    }
}

TEST(WarehouseSectionCountValidation, InvalidNegative)
{
    const int test_data[] = {-1, -101, -2132, -44545444, -1003};
    for (auto &&test : test_data)
    {
        EXPECT_NE(ValidateWarehouseSectionCount(test), 0) << "Failed for input: " << test;
    }
}

TEST(WarehouseIdValidation, Valid)
{
    const std::string test_data[] = {"AB234", "SD121", "RS001", "AB235", "CD898"};
    for (auto &&test : test_data)
    {
        EXPECT_EQ(ValidateWarehouseId(test.c_str()), 0) << "Failed for input: " << test;
    }
}

TEST(WarehouseIdValidation, InvalidCharacters)
{
    const std::string test_data[] = {"Aa234", "sD121", "RSR01", "D1S21", "2AB35", "898CD"};
    for (auto &&test : test_data)
    {
        EXPECT_NE(ValidateWarehouseId(test.c_str()), 0) << "Failed for input: " << test;
    }
}

TEST(WarehouseIdValidation, InvalidLength)
{
    const std::string test_data[] = {"AB2345", "SDS121", "001RSR", "23ABB5", "CD8D98"};
    for (auto &&test : test_data)
    {
        EXPECT_NE(ValidateWarehouseId(test.c_str()), 0) << "Failed for input: " << test;
    }
}

TEST(WarehouseNameValidation, Valid)
{
    const std::string test_data[] = {"R12", "R20", "Zestaw baterii", "A5 Zeszyt", "Zeszyt 100 kartek"};
    for (auto &&test : test_data)
    {
        EXPECT_EQ(ValidateWarehouseName(test.c_str()), 0) << "Failed for input: " << test;
    }
}

TEST(WarehouseNameValidation, Invalid)
{
    const std::string test_data[] = {"123", "Gadget_XYZ", "Tool-Set"};
    for (auto &&test : test_data)
    {
        EXPECT_NE(ValidateWarehouseName(test.c_str()), 0) << "Failed for input: " << test;
    }
}

TEST(PrintFilenameValidation, Valid)
{
    const std::string test_data[] = {"file", "o", "exactlyten"};
    for (auto &&test : test_data)
    {
        EXPECT_EQ(ValidatePrintFilename(test.c_str()), 0) << "Failed for input: " << test;
    }
}

TEST(PrintFilenameValidation, InvalidFirstCharacter)
{
    const std::string test_data[] = {"1file", "0name"
                                              "9data"};
    for (auto &&test : test_data)
    {
        EXPECT_NE(ValidatePrintFilename(test.c_str()), 0) << "Failed for input: " << test;
    }
}

TEST(PrintFilenameValidation, InvalidCharacters)
{
    const std::string test_data[] = {"abc_123", "file name"
                                                "test-data"};
    for (auto &&test : test_data)
    {
        EXPECT_NE(ValidatePrintFilename(test.c_str()), 0) << "Failed for input: " << test;
    }
}

TEST(PrintFilenameValidation, InvalidLength)
{
    const std::string test_data[] = {"", "toolongfilename"
                                         "elevenlette"};
    for (auto &&test : test_data)
    {
        EXPECT_NE(ValidatePrintFilename(test.c_str()), 0) << "Failed for input: " << test;
    }
}

} // namespace