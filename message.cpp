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
    packet pkt;
    append_to(pkt);

    return pkt;
}

////////////////////////////////////////////////////////////////////////////////
void message::append_to(packet& pkt) const
{
    value::append_to(pkt, address());

    string tags = ",";
    for(auto const& v : values()) tags += v.tag();
    value::append_to(pkt, tags);

    for(auto const& v : values()) v.append_to(pkt);
}

////////////////////////////////////////////////////////////////////////////////
}
