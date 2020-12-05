////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "osc++/value.hpp"
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

using namespace internal;

////////////////////////////////////////////////////////////////////////////////
int32 value::space() const
{
         if(is_int32  ()) return osc::space(to_int32  ());
    else if(is_float32()) return osc::space(to_float32());
    else if(is_string ()) return osc::space(to_string ());
    else if(is_blob   ()) return osc::space(to_blob   ());
    else throw std::invalid_argument("osc::value::space()): invalid type");
}

////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const value& val)
{
         if(val.is_int32  ()) write_to(os, val.to_int32  ());
    else if(val.is_float32()) write_to(os, val.to_float32());
    else if(val.is_string ()) write_to(os, val.to_string ());
    else if(val.is_blob   ()) write_to(os, val.to_blob   ());
    else throw std::invalid_argument("operator<<(osc::value): invalid type");

    return os;
}

////////////////////////////////////////////////////////////////////////////////
}
