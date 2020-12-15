////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "message.hpp"
#include "packet.hpp"

#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
message::message(string s) : address_(std::move(s))
{
    // TODO: fully validate address
    if(address_.size() < 1 || address_[0] != '/') throw std::invalid_argument(
        "osc::message::message(osc::string): invalid address"
    );
}

////////////////////////////////////////////////////////////////////////////////
int32 message::space() const
{
    int32 total = 0;
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
void message::append_to(packet& p) const
{
    value::append_to(p, address());

    string tags = ",";
    for(auto const& v : values()) tags += v.tag();
    value::append_to(p, tags);

    for(auto const& v : values()) v.append_to(p);
}

////////////////////////////////////////////////////////////////////////////////
bool message::maybe(packet& p)
{
    return p.data_.size() && p.data_[0] == '/';
}

////////////////////////////////////////////////////////////////////////////////
message message::parse(packet& p)
{
    auto address = value::parse_string(p);
    message m(address);

    auto tags = value::parse_string(p);
    if(tags.size() < 1 || tags[0] != ',') throw std::invalid_argument(
        "osc::message::parse(packet&): missing ','"
    );
    tags.erase(0, 1);

    for(auto t : tags) m << value::parse(p, t);
    return m;
}

////////////////////////////////////////////////////////////////////////////////
}
