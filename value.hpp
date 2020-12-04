////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OSC_VALUE_HPP
#define OSC_VALUE_HPP

////////////////////////////////////////////////////////////////////////////////
#include "types.hpp"

#include <ostream>
#include <variant>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
class value
{
public:
    value(int32   d) : tag_('i'), value_(d) { }
    value(float32 f) : tag_('f'), value_(f) { }
    value(string  s) : tag_('s'), value_(std::move(s)) { }
    value(blob    b) : tag_('b'), value_(std::move(b)) { }

    auto tag() const { return tag_; }

    template<typename T>
    bool is() const { return std::holds_alternative<T>(value_); }
    bool is_int32() const { return is<int32>(); }
    bool is_float32() const { return is<float32>(); }
    bool is_string() const { return is<string>(); }
    bool is_blob() const { return is<blob>(); }

    template<typename T>
    auto to() const { return std::get<T>(value_); }
    auto to_int32() const { return to<int32>(); }
    auto to_float32() const { return to<float32>(); }
    auto to_string() const { return to<string>(); }
    auto to_blob() const { return to<blob>(); }

private:
    char tag_;
    std::variant<int32, float32, string, blob> value_;
};

////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream&, const value&);

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
