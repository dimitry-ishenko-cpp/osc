////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "element.hpp"
#include "packet.hpp"
#include "value.hpp"

#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
int32 element::space() const
{
         if(is_message()) return to_message().space();
    else if(is_bundle ()) return to_bundle ().space();
         else throw std::invalid_argument("osc::bundle::element::space(): invalid type");
}

////////////////////////////////////////////////////////////////////////////////
void element::append_to(packet& pkt) const
{
    value::append_to(pkt, space());

         if(is_message()) to_message().append_to(pkt);
    else if(is_bundle ()) to_bundle ().append_to(pkt);
    else throw std::invalid_argument("operator<<(osc::bundle::element): invalid type");
}

////////////////////////////////////////////////////////////////////////////////
}
