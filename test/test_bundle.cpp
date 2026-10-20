#include <cmath>
#include <osc++.hpp>
#include <gtest/gtest.h>
#include <chrono>

TEST(bundle, round_trip)
{
    osc::message msg_a{"/a"}, msg_b{"/b"};
    msg_a << 1;
    msg_b << "two";

    osc::bundle bun;
    bun << msg_a << msg_b;

    auto el = bun.to_packet().parse();
    ASSERT_TRUE(el.is_bundle());

    auto& ref = el.to_bundle();
    ASSERT_EQ(ref.elements().size(), 2u);
    EXPECT_EQ(ref.element(0).to_message().address(), "/a");
    EXPECT_EQ(ref.element(1).to_message().address(), "/b");
}

TEST(bundle, immed)
{
    osc::bundle bun;
    osc::message msg{"/foo"};
    bun << msg;

    auto el = bun.to_packet().parse();
    EXPECT_EQ(el.to_bundle().time(), osc::immed);
}

TEST(bundle, time)
{
    auto now = osc::clock::now();
    osc::bundle bun{now};
    osc::message msg{"/foo"};
    bun << msg;

    auto el = bun.to_packet().parse();
    using namespace std::chrono;
    auto diff = duration_cast<nanoseconds>(el.to_bundle().time() - now).count();

    EXPECT_LT(std::abs(diff), 1000);
}

TEST(bundle, stream)
{
    osc::bundle bun;
    osc::message in{"/in"};
    bun << in;

    osc::message out{"/out"};
    bun >> out;

    EXPECT_EQ(out.address(), "/in");
    EXPECT_TRUE(bun.elements().empty());
}

TEST(bundle, space)
{
    osc::bundle bun;
    osc::message msg_a{"/a"}, msg_b{"/b"};
    bun << msg_a << msg_b;

    EXPECT_EQ(bun.to_packet().size(), bun.space());
}

TEST(bundle, nested_round_trip)
{
    osc::bundle inner, outer;
    osc::message msg{"/foo"};

    inner << msg;
    outer << inner;

    auto el = outer.to_packet().parse();
    ASSERT_TRUE(el.is_bundle());
    ASSERT_EQ(el.to_bundle().elements().size(), 1u);
    EXPECT_TRUE(el.to_bundle().element(0).is_bundle());
}
