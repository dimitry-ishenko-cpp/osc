////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020-2025 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "osc++/types.hpp"
#include "osc++/values.hpp"

#include <string_view>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

class packet;

class message
{
public:
    ////////////////////
    message(string address);

    ////////////////////
    auto& address() const { return address_; }

    auto& values() const { return values_; }
    auto& values() { return values_; }

    auto& value(std::size_t n) const { return values_.at(n); }
    auto& value(std::size_t n) { return values_.at(n); }

    message& operator<<(osc::value v)
    {
        values_.push_back(std::move(v));
        return (*this);
    }

    template<typename T>
    message& operator>>(T& x)
    {
        x = std::move(values_.at(0).to<T>());
        values_.pop_front();
        return (*this);
    }

    int32 space() const; // space requirement
    packet to_packet() const;

    ////////////////////
    static bool maybe(std::string_view); // is this packet a message?
    static message parse(std::string_view&);

private:
    ////////////////////
    string address_;
    osc::values values_;

    string tags() const;

    void append_to(packet&) const; // append message to packet
    friend class element;
};

}
