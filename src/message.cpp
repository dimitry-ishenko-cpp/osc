////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "errors.hpp"
#include "message.hpp"
#include "packet.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
message::message(string s) : address_{ std::move(s) }
{
    if(address_.size() < 1 || address_[0] != '/') throw invalid_message{ "bad address" };
}

////////////////////////////////////////////////////////////////////////////////
int32 message::space() const
{
    int32 total = 0;

    total += value::space(address());
    total += value::space(tags());

    for(auto const& val : values()) total += val.space();

    return total;
}

////////////////////////////////////////////////////////////////////////////////
packet message::to_packet() const
{
    packet p;
    append_to(p);

    return p;
}

////////////////////////////////////////////////////////////////////////////////
bool message::maybe(packet& p)
{
    return p.data_.size() && p.data_[0] == '/';
}

////////////////////////////////////////////////////////////////////////////////
message message::parse(packet& p)
{
    auto address = osc::value::parse_string(p);
    message m{ address };

    auto tags = osc::value::parse_string(p);
    if(tags.size() < 1 || tags[0] != ',') throw invalid_packet{ "missing ','" };
    tags.erase(0, 1);

    for(auto t : tags) m << osc::value::parse(p, t);
    return m;
}

////////////////////////////////////////////////////////////////////////////////
void message::append_to(packet& p) const
{
    osc::value::append_to(p, address());
    osc::value::append_to(p, tags());

    for(auto const& v : values()) v.append_to(p);
}

////////////////////////////////////////////////////////////////////////////////
string message::tags() const
{
    string tags = ",";
    for(auto const& v : values()) tags += v.tag();
    return tags;
}

////////////////////////////////////////////////////////////////////////////////
}
