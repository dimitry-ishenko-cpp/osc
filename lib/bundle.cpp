////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020-2025 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "osc++/bundle.hpp"
#include "osc++/elements.hpp"
#include "osc++/errors.hpp"
#include "osc++/packet.hpp"
#include "osc++/value.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

bundle& bundle::operator<<(osc::element e)
{
    elements_.push_back(std::move(e));
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
bundle& bundle::operator>>(message& m)
{
    auto e = std::move(elements_.front());
    elements_.pop_front();

    m = std::move(e.to_message());
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////
bundle& bundle::operator>>(bundle& b)
{
    auto e = std::move(elements_.front());
    elements_.pop_front();

    b = std::move(e.to_bundle());
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////
int32 bundle::space() const
{
    int32 total = value::space(string{"#bundle"}) + value::space(time());
    for (auto&& e : elements()) total += sizeof(int32) + e.space();
    return total;
}

////////////////////////////////////////////////////////////////////////////////
packet bundle::to_packet() const
{
    packet p;
    append_to(p);
    return p;
}

////////////////////////////////////////////////////////////////////////////////
void bundle::append_to(packet& p) const
{
    value::append_to(p, string{"#bundle"});
    value::append_to(p, time());

    for (auto&& e : elements())
    {
        value::append_to(p, e.space());
        e.append_to(p);
    }
}

////////////////////////////////////////////////////////////////////////////////
bool bundle::maybe(std::string_view p)
{
    return p.size() && p[0] == '#';
}

////////////////////////////////////////////////////////////////////////////////
bundle bundle::parse(std::string_view& p)
{
    if (value::parse_string(p) != "#bundle") throw invalid_bundle{"missing '#bundle'"};

    bundle b{value::parse_time(p)};
    while (p.size())
    {
        auto size = value::parse_int32(p);
        auto e = packet::take(p, size);

        b << osc::element::parse(e);
    }
    return b;
}

}
