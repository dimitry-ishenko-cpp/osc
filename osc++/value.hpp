////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OSC_VALUE_HPP
#define OSC_VALUE_HPP

////////////////////////////////////////////////////////////////////////////////
#include "osc++/types.hpp"

#include <ostream>
#include <variant>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
class value
{
public:
    value(int32  d) : tag_('i'), value_(d) { }
    value(float  f) : tag_('f'), value_(f) { }
    value(string s) : tag_('s'), value_(std::move(s)) { }
    value(blob   b) : tag_('b'), value_(std::move(b)) { }

    auto tag() const { return tag_; }

    template<typename T>
    bool is() const { return std::holds_alternative<T>(value_); }
    bool is_int32 () const { return is<int32 >(); }
    bool is_float () const { return is<float >(); }
    bool is_string() const { return is<string>(); }
    bool is_blob  () const { return is<blob  >(); }

    template<typename T>
    auto const& to() const { return std::get<T>(value_); }
    auto const& to_int32 () const { return to<int32 >(); }
    auto const& to_float () const { return to<float >(); }
    auto const& to_string() const { return to<string>(); }
    auto const& to_blob  () const { return to<blob  >(); }

    int32 space() const;

private:
    char tag_;
    std::variant<int32, float, string, blob> value_;
};

////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream&, const value&);

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
