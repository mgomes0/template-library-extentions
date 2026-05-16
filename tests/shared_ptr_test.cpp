#include <iostream>

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
    EXPECT_EQ(p.get(), nullptr);
    EXPECT_EQ(p, nullptr);
    EXPECT_EQ(nullptr, p);
}


TEST(SharedPtrTest, MakeSharedCreatesObject) {
    auto p = stlx::make_shared<Widget>();
    p->value = 42;
    EXPECT_EQ(p->value, 42);
    EXPECT_EQ((*p).value, 42);
    EXPECT_NE(p, nullptr);

    auto q = stlx::make_shared<Widget>();
    EXPECT_NE(p, q);

    EXPECT_EQ(p.use_count(), 1);
    EXPECT_EQ(q.use_count(), 1);
}


TEST(SharedPtrTest, CopyIncreasesRefCount) {
    auto p = stlx::make_shared<Widget>();
    EXPECT_EQ(p.use_count(), 1);
    {
        stlx::shared_ptr<Widget> q(p);
        EXPECT_EQ(q.use_count(), 2);
    }
    EXPECT_EQ(p.use_count(), 1);
}


//TEST(SharedPtrTest, MoveTransfersOwnership) {
////    auto p1 = tlex::make_shared<Widget>(7);
////    tlex::shared_ptr<Widget> p2(std::move(p1));
////    EXPECT_EQ(p1.operator->(), nullptr);  // NOLINT: testing moved-from state
////    EXPECT_EQ(p2->value, 7);
////    EXPECT_EQ(p2->use_count(), 1u);
//    GTEST_SKIP() << "Not yet implemented";
//}
//
//TEST(SharedPtrTest, DerivedToCopyAssignment) {
////    auto derived = tlex::make_shared<Gadget>(99);
////    tlex::shared_ptr<Widget> base;
////    base = derived;
////    EXPECT_EQ(base->value, 99);
////    EXPECT_EQ(derived->use_count(), 2u);
//    GTEST_SKIP() << "Not yet implemented";
//}
