////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OSC_TYPES_HPP
#define OSC_TYPES_HPP

////////////////////////////////////////////////////////////////////////////////
#include <chrono>
#include <cstddef>
#include <ostream>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

using clock = std::chrono::system_clock;

////////////////////////////////////////////////////////////////////////////////
using int32   = std::int32_t;
using string  = std::string;
using blob    = std::vector<char>;
using int64   = std::int64_t;
using time    = clock::time_point;
using null    = std::nullptr_t;

struct inf_t { explicit inf_t() = default; };

////////////////////////////////////////////////////////////////////////////////
namespace literals
{

constexpr auto nil = nullptr;
constexpr inf_t inf { };

}
using namespace literals;

////////////////////////////////////////////////////////////////////////////////
namespace internal
{

void write_to(std::ostream&, int32 );
void write_to(std::ostream&, float );
void write_to(std::ostream&, string);
void write_to(std::ostream&, blob  );
void write_to(std::ostream&, int64 );
void write_to(std::ostream&, time  );
void write_to(std::ostream&, double);
void write_to(std::ostream&, char  );
void write_to(std::ostream&, bool  );
void write_to(std::ostream&, null  );
void write_to(std::ostream&, inf_t );

inline int32 padded(int32 x) { return ((x + 3) / 4) * 4; }

}

////////////////////////////////////////////////////////////////////////////////
inline int32 space(int32 ) { return sizeof(int32 ); }
inline int32 space(float ) { return sizeof(float ); }
inline int32 space(const string& s) { return internal::padded(s.size() + 1); }
inline int32 space(const blob& b) { return space(int32{}) + internal::padded(b.size()); }
inline int32 space(int64 ) { return sizeof(int64 ); }
inline int32 space(time  ) { return sizeof(int64 ); } // sent as int64
inline int32 space(double) { return sizeof(double); }
inline int32 space(char  ) { return sizeof(int32 ); } // sent as int32
inline int32 space(bool  ) { return 0; }
inline int32 space(null  ) { return 0; }
inline int32 space(inf_t ) { return 0; }

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
