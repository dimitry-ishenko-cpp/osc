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
void element::append_to(packet& p) const
{
    value::append_to(p, space());

         if(is_message()) to_message().append_to(p);
    else if(is_bundle ()) to_bundle ().append_to(p);
    else throw std::invalid_argument("operator<<(osc::bundle::element): invalid type");
}

////////////////////////////////////////////////////////////////////////////////
bool element::maybe(packet& p)
{
    return p.size() && !message::maybe(p) && !bundle::maybe(p);
}

////////////////////////////////////////////////////////////////////////////////
element element::parse(packet& p)
{
    auto size = p.size() - value::parse_int32(p); // remaining packet size after this element

    auto e = message::maybe(p) ? element(message::parse(p)) :
        bundle::maybe(p) ? element(bundle::parse(p)) :
    throw std::invalid_argument("osc::element::parse(osc::packet&): invalid element");

    auto pad = size - p.size();
    if(pad < 0 || pad > 3) throw std::invalid_argument(
        "osc::element::parse(osc::packet&): invalid packet"
    );
    p.data_.erase(p.data_.begin(), p.data_.begin() + pad);

    return e;
}

////////////////////////////////////////////////////////////////////////////////
}
