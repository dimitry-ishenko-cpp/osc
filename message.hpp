////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OSC_MESSAGE_HPP
#define OSC_MESSAGE_HPP

////////////////////////////////////////////////////////////////////////////////
#include "types.hpp"
#include "values.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

class packet;

////////////////////////////////////////////////////////////////////////////////
class message
{
public:
    message(string address);

    auto const& address() const { return address_; }

    auto const& values() const { return values_; }
    auto& values() { return values_; }

    auto const& value(std::size_t n) const { return values_[n]; }
    auto& value(std::size_t n) { return values_[n]; }

    message& operator<<(osc::value v)
    {
        values_.push_back(std::move(v));
        return (*this);
    }

    template<typename T>
    message& operator>>(T& x)
    {
        auto v{ std::move(values_.front()) };
        values_.pop_front();

        x = std::move(v.to<T>());
        return (*this);
    }

    int32 space() const; // space requirement
    packet to_packet() const;

    static bool maybe(packet&); // is this packet a message?
    static message parse(packet&);

private:
    string address_;
    osc::values values_;

    string tags() const;

    void append_to(packet&) const; // append message to packet
    friend class element;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
