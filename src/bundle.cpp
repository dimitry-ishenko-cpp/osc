////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "bundle.hpp"
#include "elements.hpp"
#include "errors.hpp"
#include "packet.hpp"
#include "value.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
bundle& bundle::operator<<(osc::element e)
{
    elements_.push_back(std::move(e));
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
bundle& bundle::operator>>(message& m)
{
    auto e{ std::move(elements_.front()) };
    elements_.pop_front();

    m = std::move(e.to_message());
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////
bundle& bundle::operator>>(bundle& b)
{
    auto e{ std::move(elements_.front()) };
    elements_.pop_front();

    b = std::move(e.to_bundle());
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////
int32 bundle::space() const
{
    int32 total = 0;

    total += value::space(string("#bundle"));
    total += value::space(time());

    for(auto const& e : elements()) total += e.space();

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
    value::append_to(p, string("#bundle"));
    value::append_to(p, time());

    for(auto const& e : elements()) e.append_to(p);
}

////////////////////////////////////////////////////////////////////////////////
bool bundle::maybe(packet& p)
{
    return p.data_.size() && p.data_[0] == '#';
}

////////////////////////////////////////////////////////////////////////////////
bundle bundle::parse(packet& p)
{
    auto s = value::parse_string(p);
    if(s != "#bundle") throw invalid_bundle{ "missing '#bundle'" };

    bundle b{ value::parse_time(p) };
    while(osc::element::maybe(p)) b << osc::element::parse(p);

    return b;
}

////////////////////////////////////////////////////////////////////////////////
}
