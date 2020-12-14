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
#include <variant>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

class packet;

////////////////////////////////////////////////////////////////////////////////
class value
{
public:
    value(int32  i) : tag_('i'), value_(i) { }
    value(float  f) : tag_('f'), value_(f) { }
    value(string s) : tag_('s'), value_(std::move(s)) { }
    value(blob   b) : tag_('b'), value_(std::move(b)) { }
    value(int64  i) : tag_('h'), value_(i) { }
    value(time   t) : tag_('t'), value_(t) { }
    value(double d) : tag_('d'), value_(d) { }
    value(char   c) : tag_('c'), value_(c) { }
    value(bool   b) : tag_(b ? 'T' : 'F'), value_(b) { }
    value(null   n) : tag_('N'), value_(n) { }
    value(inf_t  i) : tag_('I'), value_(i) { }

    auto tag() const { return tag_; }

    template<typename T>
    bool is() const { return std::holds_alternative<T>(value_); }

    bool is_int32 () const { return is<int32 >(); }
    bool is_float () const { return is<float >(); }
    bool is_string() const { return is<string>(); }
    bool is_blob  () const { return is<blob  >(); }
    bool is_int64 () const { return is<int64 >(); }
    bool is_time  () const { return is<time  >(); }
    bool is_double() const { return is<double>(); }
    bool is_char  () const { return is<char  >(); }
    bool is_bool  () const { return is<bool  >(); }
    bool is_true  () const { return is_bool() &&  to_bool(); }
    bool is_false () const { return is_bool() && !to_bool(); }
    bool is_nil   () const { return is<null  >(); }
    bool is_inf   () const { return is<inf_t >(); }

    template<typename T>
    auto const& to() const { return std::get<T>(value_); }

    auto const& to_int32 () const { return to<int32 >(); }
    auto const& to_float () const { return to<float >(); }
    auto const& to_string() const { return to<string>(); }
    auto const& to_blob  () const { return to<blob  >(); }
    auto const& to_int64 () const { return to<int64 >(); }
    auto const& to_time  () const { return to<time  >(); }
    auto const& to_double() const { return to<double>(); }
    auto const& to_char  () const { return to<char  >(); }
    bool const& to_bool  () const { return to<bool  >(); }
    auto const& to_nil   () const { return to<null  >(); }
    auto const& to_inf   () const { return to<inf_t >(); }

    int32 space() const;

private:
    char tag_;

    std::variant<int32, float, string, blob,
        int64, time, double, char, bool, null, inf_t
    > value_;

    void append_to(packet&) const;

    static void append_to(packet&, int32);
    static void append_to(packet&, float);
    static void append_to(packet&, string);
    static void append_to(packet&, blob);
    static void append_to(packet&, int64);
    static void append_to(packet&, time);
    static void append_to(packet&, double);
    static void append_to(packet&, char);
    static void append_to(packet&, bool ) { }
    static void append_to(packet&, null ) { }
    static void append_to(packet&, inf_t) { }

    friend class bundle;
    friend class element;
    friend class message;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
