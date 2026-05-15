#include <stlx/vector.hpp>

#include <gtest/gtest.h>


TEST(VectorTest, DefaultConstructedIsEmpty) {
    stlx::vector<int> v;
    v.push_back(4);
//    GTEST_SKIP() << "Not yet implemented";
}

TEST(VectorTest, PushBackIncreasesSize) {
    // tlex::vector<int> v;
    // v.push_back(42);
    // EXPECT_EQ(v.size(), 1u);
    // EXPECT_EQ(v[0], 42);
    GTEST_SKIP() << "Not yet implemented";
}
