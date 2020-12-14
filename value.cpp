////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "packet.hpp"
#include "value.hpp"

#include <stdexcept>
#include <endian.h>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
namespace
{

int32 padded(int32 x) { return ((x + 3) / 4) * 4; }

int32 space_(int32 ) { return sizeof(int32 ); }
int32 space_(float ) { return sizeof(float ); }
int32 space_(const string& s) { return padded(s.size() + 1); }
int32 space_(const blob& b) { return space_(int32{}) + padded(b.size()); }
int32 space_(int64 ) { return sizeof(int64 ); }
int32 space_(time  ) { return sizeof(int64 ); } // sent as int64
int32 space_(double) { return sizeof(double); }
int32 space_(char  ) { return sizeof(int32 ); } // sent as int32
int32 space_(bool  ) { return 0; }
int32 space_(null  ) { return 0; }
int32 space_(inf_t ) { return 0; }

}

////////////////////////////////////////////////////////////////////////////////
int32 value::space() const
{
         if(is_int32 ()) return space_( to_int32 ());
    else if(is_float ()) return space_( to_float ());
    else if(is_string()) return space_( to_string());
    else if(is_blob  ()) return space_( to_blob  ());
    else if(is_int64 ()) return space_( to_int64 ());
    else if(is_time  ()) return space_( to_time  ());
    else if(is_double()) return space_( to_double());
    else if(is_char  ()) return space_( to_char  ());
    else if(is_bool  ()) return space_( to_bool  ());
    else if(is_nil   ()) return space_( to_nil   ());
    else if(is_inf   ()) return space_( to_inf   ());
    else throw std::invalid_argument("osc::value::space()): invalid type");
}

////////////////////////////////////////////////////////////////////////////////
void value::append_to(packet& pkt) const
{
         if(is_int32 ()) append_to(pkt, to_int32 ());
    else if(is_float ()) append_to(pkt, to_float ());
    else if(is_string()) append_to(pkt, to_string());
    else if(is_blob  ()) append_to(pkt, to_blob  ());
    else if(is_int64 ()) append_to(pkt, to_int64 ());
    else if(is_time  ()) append_to(pkt, to_time  ());
    else if(is_double()) append_to(pkt, to_double());
    else if(is_char  ()) append_to(pkt, to_char  ());
    else if(is_bool  ()) append_to(pkt, to_bool  ());
    else if(is_nil   ()) append_to(pkt, to_nil   ());
    else if(is_inf   ()) append_to(pkt, to_inf   ());
    else throw std::invalid_argument("osc::value::append_to(osc::packet&): invalid type");
}

////////////////////////////////////////////////////////////////////////////////
void value::append_to(packet& p, int32 i)
{
    i = htobe32(i);
    p.append(reinterpret_cast<char*>(&i), sizeof(i));
}

////////////////////////////////////////////////////////////////////////////////
void value::append_to(packet& p, float f)
{
    append_to(p, *reinterpret_cast<int32*>(&f));
}

////////////////////////////////////////////////////////////////////////////////
void value::append_to(packet& p, string s)
{
    s.resize(padded(s.size() + 1));
    p.append(s.data(), s.size());
}

////////////////////////////////////////////////////////////////////////////////
void value::append_to(packet& p, blob b)
{
    append_to(p, static_cast<int32>(b.size()));
    b.resize(padded(b.size()));
    p.append(b.data(), b.size());
}

////////////////////////////////////////////////////////////////////////////////
void value::append_to(packet& p, int64 i)
{
    i = htobe64(i);
    p.append(reinterpret_cast<char*>(&i), sizeof(i));
}

////////////////////////////////////////////////////////////////////////////////
void value::append_to(packet& p, time t)
{
    using namespace std::chrono;
    using namespace std::chrono_literals;

    using fractions = duration<int64, std::ratio<1, 0x100000000>>; // 1/(2^32)

    // "shift" epoch from 1/1/1970 (unix) to 1/1/1900 (osc)
    // which is 70 years + 17 leap days
    // ref: https://stackoverflow.com/a/65149566/4358570
    t += (70 * 365 + 17) * 24h;

    auto total = t.time_since_epoch();
    auto sec = duration_cast<seconds>(total);
    auto frac = duration_cast<fractions>(total - sec);

    append_to(p, static_cast<int64>((sec.count() << 32) | frac.count()));
}

////////////////////////////////////////////////////////////////////////////////
void value::append_to(packet& p, double d)
{
    append_to(p, *reinterpret_cast<int64*>(&d));
}

////////////////////////////////////////////////////////////////////////////////
void value::append_to(packet& p, char c)
{
    append_to(p, static_cast<int32>(c));
}

////////////////////////////////////////////////////////////////////////////////
}
