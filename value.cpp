////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "value.hpp"
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

using namespace internal;

////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const value& val)
{
         if(val.is_int32  ()) write_to(os, val.to_int32  ());
    else if(val.is_float32()) write_to(os, val.to_float32());
    else if(val.is_string ()) write_to(os, val.to_string ());
    else if(val.is_blob   ()) write_to(os, val.to_blob   ());
    else std::invalid_argument("operator<<(osc::value): invalid value type");

    return os;
}

////////////////////////////////////////////////////////////////////////////////
}
