#include <gtest/gtest.h>

extern "C"
{
#include "validator.h"
}

TEST(WarehouseSizeValidation, Valid)
{
    const int sizes[] = {1, 1000, 9, 257, 513};
    for (const int size : sizes)
    {
        EXPECT_EQ(ValidateWarehouseSize(size), 0);
    }
}

TEST(WarehouseSizeValidation, InvalidPositive)
{
    const int sizes[] = {0, 1001, 21321231, 44545444, 1203};
    for (const int size : sizes)
    {
        EXPECT_NE(ValidateWarehouseSize(size), 0);
    }
}

TEST(WarehouseSizeValidation, InvalidNegative)
{
    const int sizes[] = {-1, -1001, -21321231, -44545444, -1203};
    for (const int size : sizes)
    {
        EXPECT_NE(ValidateWarehouseSize(size), 0);
    }
}

TEST(ProductIdValidation, Valid)
{
    const char *id[] = {"AB234", "SD121", "RS001", "AB235", "CD898"};
    for (const char *ids : id)
    {
        EXPECT_EQ(ValidateProductId(ids), 0);
    }
}

TEST(ProductIdValidation, InvalidCharacters)
{
    const char *id[] = {"Aa234", "sD121", "RSR01", "D1S21", "2AB35", "898CD"};
    for (const char *ids : id)
    {
        EXPECT_NE(ValidateProductId(ids), 0);
    }
}

TEST(ProductIdValidation, InvalidLength)
{
    const char *id[] = {"AB2345", "SDS121", "001RSR", "23ABB5", "CD8D98"};
    for (const char *ids : id)
    {
        EXPECT_NE(ValidateProductId(ids), 0);
    }
}

TEST(ProductNameValidation, Valid)
{
    const char *names[] = {"R12", "R20", "Zestaw baterii", "A5 Zeszyt", "Zeszyt 100 kartek"};
    for (const char *name : names)
    {
        EXPECT_EQ(ValidateProductName(name), 0);
    }
}

TEST(ProductNameValidation, Invalid)
{
    const char *names[] = {"123", "Gadget_XYZ", "Tool-Set"};
    for (const char *name : names)
    {
        EXPECT_NE(ValidateProductName(name), 0);
    }
}