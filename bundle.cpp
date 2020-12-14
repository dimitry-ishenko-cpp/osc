////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "bundle.hpp"
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
int32 bundle::space() const
{
    int32 total = 0;
    for(auto const& e : elements()) total += e.space();
    return total;
}

////////////////////////////////////////////////////////////////////////////////
packet bundle::to_packet() const
{
    packet pkt;
    append_to(pkt);

    return pkt;
}

////////////////////////////////////////////////////////////////////////////////
void bundle::append_to(packet& pkt) const
{
    value::append_to(pkt, string("#bundle"));
    value::append_to(pkt, time());

    for(auto const& e : elements()) e.append_to(pkt);
}

////////////////////////////////////////////////////////////////////////////////
int32 bundle::element::space() const
{
         if(is_message()) return to_message().space();
    else if(is_bundle ()) return to_bundle ().space();
         else throw std::invalid_argument("osc::bundle::element::space(): invalid type");
}

////////////////////////////////////////////////////////////////////////////////
void bundle::element::append_to(packet& pkt) const
{
    value::append_to(pkt, space());

         if(is_message()) to_message().append_to(pkt);
    else if(is_bundle ()) to_bundle ().append_to(pkt);
    else throw std::invalid_argument("operator<<(osc::bundle::element): invalid type");
}

////////////////////////////////////////////////////////////////////////////////
}
