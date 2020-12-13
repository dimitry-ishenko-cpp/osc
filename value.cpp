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
         if(is_int32 ()) return osc::space(to_int32 ());
    else if(is_float ()) return osc::space(to_float ());
    else if(is_string()) return osc::space(to_string());
    else if(is_blob  ()) return osc::space(to_blob  ());
    else if(is_int64 ()) return osc::space(to_int64 ());
    else if(is_time  ()) return osc::space(to_time  ());
    else if(is_double()) return osc::space(to_double());
    else if(is_char  ()) return osc::space(to_char  ());
    else if(is_bool  ()) return osc::space(to_bool  ());
    else if(is_nil   ()) return osc::space(to_nil   ());
    else if(is_inf   ()) return osc::space(to_inf   ());
    else throw std::invalid_argument("osc::value::space()): invalid type");
}

////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const value& val)
{
         if(val.is_int32 ()) write_to(os, val.to_int32 ());
    else if(val.is_float ()) write_to(os, val.to_float ());
    else if(val.is_string()) write_to(os, val.to_string());
    else if(val.is_blob  ()) write_to(os, val.to_blob  ());
    else if(val.is_int64 ()) write_to(os, val.to_int64 ());
    else if(val.is_time  ()) write_to(os, val.to_time  ());
    else if(val.is_double()) write_to(os, val.to_double());
    else if(val.is_char  ()) write_to(os, val.to_char  ());
    else if(val.is_bool  ()) write_to(os, val.to_bool  ());
    else if(val.is_nil   ()) write_to(os, val.to_nil   ());
    else if(val.is_inf   ()) write_to(os, val.to_inf   ());
    else throw std::invalid_argument("operator<<(osc::value): invalid type");

    return os;
}

////////////////////////////////////////////////////////////////////////////////
}
