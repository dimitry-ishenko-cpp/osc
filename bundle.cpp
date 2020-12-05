////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "osc++/bundle.hpp"
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

using namespace internal;

////////////////////////////////////////////////////////////////////////////////
int32 bundle::space() const
{
    int32 total = 0;
    for(auto const& elem : elements()) total += elem.space();
    return total;
}

////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const bundle& b)
{
    write_to(os, string("#bundle"));
    write_to(os, b.time());

    for(auto const& e : b.elements()) os << e;

    return os;
}

////////////////////////////////////////////////////////////////////////////////
int32 bundle::element::space() const
{
         if(is_message()) return to_message().space();
    else if(is_bundle ()) return to_bundle ().space();
    else throw std::invalid_argument("osc::bundle::element::space(): invalid type");
}

////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const bundle::element& e)
{
    write_to(os, e.space());
         if(e.is_message()) os << e.to_message();
    else if(e.is_bundle ()) os << e.to_bundle ();
    else throw std::invalid_argument("operator<<(osc::bundle::element): invalid type");
    return os;
}

////////////////////////////////////////////////////////////////////////////////
}
