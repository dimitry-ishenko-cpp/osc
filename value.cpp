////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "value.hpp"

#include <stdexcept>
#include <arpa/inet.h>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
namespace
{

void write(std::ostream& os, int32 i)
{
    auto ni = htonl(i);
    os.write(reinterpret_cast<char*>(&ni), sizeof(ni));
}

}

////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const value& val)
{
    if(val.is_int32())
    {
        write(os, val.to_int32());
    }
    else if(val.is_float32())
    {
        auto f = val.to_float32();
        write(os, *reinterpret_cast<int32*>(&f));
    }
    else if(val.is_string())
    {
        auto s = val.to_string();

        // add terminating null and pad to multiple of 4
        s.resize(((s.size() + 4) / 4) * 4);
        os.write(s.data(), s.size());
    }
    else if(val.is_blob())
    {
        auto b = val.to_blob();

        write(os, b.size());
        // pad to multiple of 4
        b.resize(((b.size() + 3) / 4) * 4);
        os.write(b.data(), b.size());
    }
    else std::invalid_argument("operator<<: invalid value type");

    return os;
}

////////////////////////////////////////////////////////////////////////////////
}
