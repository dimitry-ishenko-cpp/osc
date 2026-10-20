#include <osc++.hpp>
#include <gtest/gtest.h>
#include <variant>

TEST(value, type_tags)
{
    EXPECT_EQ(osc::value{42   }.tag(), 'i');
    EXPECT_EQ(osc::value{1.5f }.tag(), 'f');
    EXPECT_EQ(osc::value{"hi" }.tag(), 's');
    EXPECT_EQ(osc::value{osc::int64{1}}.tag(), 'h');
    EXPECT_EQ(osc::value{2.5  }.tag(), 'd');
    EXPECT_EQ(osc::value{'x'  }.tag(), 'c');
    EXPECT_EQ(osc::value{true }.tag(), 'T');
    EXPECT_EQ(osc::value{false}.tag(), 'F');
    EXPECT_EQ(osc::value{osc::nil}.tag(), 'N');
    EXPECT_EQ(osc::value{osc::inf}.tag(), 'I');
}

TEST(value, is_and_to)
{
    osc::value v{42};
    EXPECT_TRUE (v.is_int32());
    EXPECT_FALSE(v.is_string());
    EXPECT_EQ   (v.to_int32(), 42);

    osc::value s{"hello"};
    EXPECT_TRUE (s.is_string());
    EXPECT_EQ   (s.to_string(), "hello");
}

TEST(value, bool_helpers)
{
    EXPECT_TRUE (osc::value{true }.is_true ());
    EXPECT_FALSE(osc::value{true }.is_false());
    EXPECT_TRUE (osc::value{false}.is_false());
}

TEST(value, wrong_type)
{
    osc::value v{42};
    EXPECT_THROW(v.to_string(), std::bad_variant_access);
}

TEST(value, space)
{
    EXPECT_EQ(osc::value{42    }.space(), 4);
    EXPECT_EQ(osc::value{osc::int64{1}}.space(), 8);
    EXPECT_EQ(osc::value{"abc" }.space(), 4);
    EXPECT_EQ(osc::value{"abcd"}.space(), 8);
    EXPECT_EQ(osc::value{true  }.space(), 0);
}
