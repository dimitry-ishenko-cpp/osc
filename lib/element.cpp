////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020-2025 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "osc++/element.hpp"
#include "osc++/errors.hpp"
#include "osc++/packet.hpp"
#include "osc++/value.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

int32 element::space() const
{
         if (is_message()) return to_message().space();
    else if (is_bundle ()) return to_bundle ().space();
    else throw invalid_element{"bad type"};
}

////////////////////////////////////////////////////////////////////////////////
void element::append_to(packet& p) const
{
         if (is_message()) to_message().append_to(p);
    else if (is_bundle ()) to_bundle ().append_to(p);
    else throw invalid_element{"bad type"};
}

////////////////////////////////////////////////////////////////////////////////
element element::parse(std::string_view& p)
{
    if (message::maybe(p)) return message::parse(p);
    if (bundle ::maybe(p)) return bundle ::parse(p);

    throw invalid_packet{"neither message nor bundle"};
}

}
