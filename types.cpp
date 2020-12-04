////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "types.hpp"
#include <endian.h>

////////////////////////////////////////////////////////////////////////////////
namespace osc::internal
{

////////////////////////////////////////////////////////////////////////////////
void write_to(std::ostream& os, int32 i)
{
    i = htobe32(i);
    os.write(reinterpret_cast<char*>(&i), sizeof(i));
}

////////////////////////////////////////////////////////////////////////////////
void write_to(std::ostream& os, float32 f)
{
    write_to(os, *reinterpret_cast<int32*>(&f));
}

////////////////////////////////////////////////////////////////////////////////
void write_to(std::ostream& os, string s)
{
    s.resize(space(s));
    os.write(s.data(), s.size());
}

////////////////////////////////////////////////////////////////////////////////
void write_to(std::ostream& os, blob b)
{
    write_to(os, static_cast<int32>(b.size()));
    b.resize(space(b));
    os.write(b.data(), b.size());
}

////////////////////////////////////////////////////////////////////////////////
void write_to(std::ostream& os, int64 i)
{
    i = htobe64(i);
    os.write(reinterpret_cast<char*>(&i), sizeof(i));
}

////////////////////////////////////////////////////////////////////////////////
void write_to(std::ostream& os, osc::time time)
{
    using namespace std::chrono;
    using namespace std::chrono_literals;

    using sec_t = duration<int64, std::ratio<1, 1>>;
    using frac_t = duration<int64, std::ratio<1, 0x100000000>>; // 1/(2^32)

    // "shift" epoch from 1/1/1970 (unix) to 1/1/1900 (osc)
    // which is 70 years + 17 leap days (https://stackoverflow.com/a/29138806/4358570)
    time += (70 * 365 + 17) * 24h;

    auto total = time.time_since_epoch(); // total duration
    auto sec = duration_cast<sec_t>(total); // seconds
    auto frac = duration_cast<frac_t>(total) - sec; // fractions

    write_to(os, static_cast<int64>((sec.count() << 32) | frac.count()));
}

////////////////////////////////////////////////////////////////////////////////
}
