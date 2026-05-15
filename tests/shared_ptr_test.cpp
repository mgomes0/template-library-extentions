#include <stlx/shared_ptr.hpp>

#include <gtest/gtest.h>


struct Widget : public stlx::instrument_for_shared_ptr {
int value;
};


struct Gadget : public Widget {
float other_value;
};


TEST(SharedPtrTest, DefaultConstructedIsNull) {
    stlx::shared_ptr<Widget> p;
    stlx::shared_ptr<Gadget> g;
//    EXPECT_EQ(p, nullptr);
}

TEST(SharedPtrTest, MakeSharedCreatesObject) {
//    auto p = tlex::make_shared<Widget>(42);
//    EXPECT_EQ(p->value, 42);
//    EXPECT_EQ((*p).value, 42);
    GTEST_SKIP() << "Not yet implemented";
}

TEST(SharedPtrTest, CopyIncreasesRefCount) {
//    auto p1 = tlex::make_shared<Widget>(1);
//    {
//        tlex::shared_ptr<Widget> p2(p1);
//        EXPECT_EQ(p1->use_count(), 2u);
//    }
//    // p2 destroyed — count back to 1, object still alive
//    EXPECT_EQ(p1->use_count(), 1u);
//    EXPECT_EQ(p1->value, 1);
    GTEST_SKIP() << "Not yet implemented";
}

TEST(SharedPtrTest, MoveTransfersOwnership) {
//    auto p1 = tlex::make_shared<Widget>(7);
//    tlex::shared_ptr<Widget> p2(std::move(p1));
//    EXPECT_EQ(p1.operator->(), nullptr);  // NOLINT: testing moved-from state
//    EXPECT_EQ(p2->value, 7);
//    EXPECT_EQ(p2->use_count(), 1u);
    GTEST_SKIP() << "Not yet implemented";
}

TEST(SharedPtrTest, DerivedToCopyAssignment) {
//    auto derived = tlex::make_shared<Gadget>(99);
//    tlex::shared_ptr<Widget> base;
//    base = derived;
//    EXPECT_EQ(base->value, 99);
//    EXPECT_EQ(derived->use_count(), 2u);
    GTEST_SKIP() << "Not yet implemented";
}
