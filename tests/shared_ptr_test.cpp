#include <iostream>

#include <stlx/shared_ptr.hpp>

#include <gtest/gtest.h>


inline std::uint64_t DESTRUCTOR_CALLS;


struct Widget : public stlx::instrument_for_shared_ptr {
int value;

public:
    ~Widget() {
        DESTRUCTOR_CALLS++;
    }
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
    DESTRUCTOR_CALLS = 0;
    {
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
    EXPECT_EQ(DESTRUCTOR_CALLS, 2);
}


TEST(SharedPtrTest, CopyIncreasesRefCount) {
    DESTRUCTOR_CALLS = 0;
    {
        auto p = stlx::make_shared<Widget>();
        EXPECT_EQ(p.use_count(), 1);
        {
            stlx::shared_ptr<Widget> q(p);
            q = p;
            EXPECT_EQ(q.use_count(), 2);
        }
        EXPECT_EQ(p.use_count(), 1);
    }
    EXPECT_EQ(DESTRUCTOR_CALLS, 1);
}


TEST(SharedPtrTest, MoveTransfersOwnership) {
    DESTRUCTOR_CALLS = 0;
    {
        auto p = stlx::make_shared<Widget>();
        EXPECT_NE(p, nullptr);

        auto p_raw = p.get();
        stlx::shared_ptr<Widget> q(std::move(p));
        EXPECT_EQ(q.get(), p_raw);
        EXPECT_EQ(p, nullptr);
    }
    EXPECT_EQ(DESTRUCTOR_CALLS, 1);
}


TEST(SharedPtrTest, DerivedToBaseConversion) {
    DESTRUCTOR_CALLS = 0;
    {
        auto derived = stlx::make_shared<Gadget>();
        derived->value = 42;
        stlx::shared_ptr<Widget> base(derived);
        EXPECT_EQ(base->value, 42);
        EXPECT_EQ(derived.use_count(), 2);
    }
    EXPECT_EQ(DESTRUCTOR_CALLS, 1);
}


TEST(SharedPtrTest, DerivedToCopyAssignment) {
    DESTRUCTOR_CALLS = 0;
    {
        auto derived = stlx::make_shared<Gadget>();
        derived->value = 42;
        stlx::shared_ptr<Widget> base;
        base = derived;
        EXPECT_EQ(base->value, 42);
        EXPECT_EQ(derived.use_count(), 2);
    }
    EXPECT_EQ(DESTRUCTOR_CALLS, 1);
}
