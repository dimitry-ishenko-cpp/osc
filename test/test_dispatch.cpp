#include <osc++.hpp>
#include <gtest/gtest.h>

TEST(dispatch, match)
{
    osc::address_space space;
    int count = 0;
    space.add("/foo/.*", [&](const osc::message&) { ++count; });

    osc::message msg{"/foo/bar"};
    EXPECT_EQ(space.dispatch(msg), 1u);
    EXPECT_EQ(count, 1);
}

TEST(dispatch, no_match)
{
    osc::address_space space;
    int count = 0;
    space.add("/foo", [&](const osc::message&) { ++count; });

    osc::message msg{"/bar"};
    EXPECT_EQ(space.dispatch(msg), 0u);
    EXPECT_EQ(count, 0);
}

TEST(dispatch, multiple_match)
{
    osc::address_space space;
    int count = 0;
    space.add("/foo", [&](const osc::message&) { ++count; });
    space.add("/.*",  [&](const osc::message&) { ++count; });

    osc::message msg{"/foo"};
    EXPECT_EQ(space.dispatch(msg), 2u);
    EXPECT_EQ(count, 2);
}

TEST(dispatch, bundle)
{
    osc::address_space space;
    int count = 0;
    space.add("/a", [&](const osc::message&) { ++count; });

    osc::bundle bun;
    osc::message msg_a{"/a"}, msg_b{"/b"};
    bun << msg_a << msg_b << msg_a;

    EXPECT_EQ(space.dispatch(bun), 2u);
    EXPECT_EQ(count, 2);
}

TEST(dispatch, invalid)
{
    osc::address_space space;
    EXPECT_THROW(space.add("/foo/[", [](const osc::message&) {}), std::regex_error);
}

TEST(dispatch, time)
{
    osc::time seen{};
    osc::address_space space{
        [&](osc::time when, const osc::bound_callback& cb) { seen = when; cb(); }
    };
    space.add("/foo", [](const osc::message&) {});

    auto when = osc::clock::now();
    osc::bundle bun{when};
    osc::message msg{"/foo"};
    bun << msg;

    space.dispatch(bun);
    EXPECT_EQ(seen, when);
}
