#include <osc++.hpp>
#include <gtest/gtest.h>
#include <string>

TEST(message, address)
{
    EXPECT_THROW(osc::message{""}, osc::invalid_message);
    EXPECT_THROW(osc::message{"no/slash"}, osc::invalid_message);

    EXPECT_NO_THROW(osc::message{"/good"});
}

TEST(message, stream)
{
    osc::message msg{"/foo"};
    msg << 12345 << "bar";
    ASSERT_EQ(msg.values().size(), 2u);

    osc::int32 i = 0; osc::string s;
    msg >> i >> s;

    EXPECT_EQ(i, 12345);
    EXPECT_EQ(s, "bar");
    EXPECT_TRUE(msg.values().empty());
}

TEST(message, encode)
{
    osc::message msg{"/a"};
    msg << 42;

    auto pkt = msg.to_packet();
    const std::string expected{ '/', 'a', 0, 0, ',', 'i', 0, 0, 0, 0, 0, 42 };

    ASSERT_EQ(pkt.size(), static_cast<osc::int32>(expected.size()));
    EXPECT_EQ(std::string(pkt.data(), pkt.size()), expected);
    EXPECT_EQ(msg.space(), pkt.size());
}

TEST(message, round_trip)
{
    osc::message msg{"/foo/bar"};
    msg << 42
        << 3.5f
        << "text"
        << osc::blob{'a', 'b', 'c'}
        << osc::int64{1234567890123}
        << 2.25
        << 'z'
        << true
        << false
        << osc::nil
        << osc::inf;

    auto el = msg.to_packet().parse();
    ASSERT_TRUE(el.is_message());

    auto& ref = el.to_message();
    EXPECT_EQ(ref.address(), "/foo/bar");
    ASSERT_EQ(ref.values().size(), 11u);

    EXPECT_EQ       (ref.value(0).to_int32 (), 42);
    EXPECT_FLOAT_EQ (ref.value(1).to_float (), 3.5f);
    EXPECT_EQ       (ref.value(2).to_string(), "text");
    EXPECT_EQ       (ref.value(3).to_blob  (), (osc::blob{'a', 'b', 'c'}));
    EXPECT_EQ       (ref.value(4).to_int64 (), 1234567890123);
    EXPECT_DOUBLE_EQ(ref.value(5).to_double(), 2.25);
    EXPECT_EQ       (ref.value(6).to_char  (), 'z');
    EXPECT_TRUE     (ref.value(7).is_true  ());
    EXPECT_TRUE     (ref.value(8).is_false ());
    EXPECT_TRUE     (ref.value(9).is_nil   ());
    EXPECT_TRUE     (ref.value(10).is_inf  ());
}

TEST(message, values_are)
{
    osc::message msg{"/foo"};
    msg << 1 << "x";

    EXPECT_TRUE ((msg.values().are<osc::int32, osc::string>()));
    EXPECT_FALSE((msg.values().are<osc::string, osc::int32>()));
    EXPECT_FALSE((msg.values().are<osc::int32>()));
}

TEST(packet, garbage)
{
    osc::packet empty;
    EXPECT_THROW(empty.parse(), osc::invalid_packet);

    const char junk[] = "xxxx";
    osc::packet pkt{junk, 4};
    EXPECT_THROW(pkt.parse(), osc::invalid_packet);
}

TEST(packet, truncated)
{
    const char data[] = {'/', 'a', 0, 0, ',', 'i', 0, 0};
    osc::packet pkt{data, 8};

    EXPECT_THROW(pkt.parse(), osc::invalid_packet);
}

TEST(packet, bad_tag)
{
    const char data[] = {'/', 'a', 0, 0, ',', 'z', 0, 0};
    osc::packet pkt{data, 8};
    EXPECT_THROW(pkt.parse(), osc::invalid_value);
}
